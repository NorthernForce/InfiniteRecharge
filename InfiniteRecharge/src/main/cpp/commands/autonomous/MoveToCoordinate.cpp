/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Version 1.1

#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/TurnToAngle.h"
#include <memory>
#include <cmath>
#include "subsystems/Drivetrain.h"
#include "Robot.h"
#include <vector>

std::unique_ptr<Logger> Robot::logger;

MoveToCoordinate::MoveToCoordinate(int xPos, int yPos, double speed) : baseSpeed(speed) {
  AddRequirements(RobotContainer::drivetrain.get());
  SetName("MoveToCoordinate");
  xFinal = xPos;
  yFinal = yPos;
  movementStage = 0;
  origAngleToFinal = RobotContainer::navigation->AngleToPoint(xFinal, yFinal);
}

// Called when the command is initially scheduled.
void MoveToCoordinate::Initialize() {
  previousDistanceError = sqrt((xFinal - xCurrent) * (xFinal - xCurrent) + (yFinal - yCurrent) * (yFinal - yCurrent));
}

// double MoveToCoordinate::RemoveJumps(double angToFinalWithJumps) {
//   bool close = false;
//   for (unsigned i = 0; i < previousAngToFinals.size(); i++) {
//     if ((angToFinal < previousAngToFinals[i] + 1) && (angToFinal > previousAngToFinals[i] - 1)) {
//       previousAngToFinals.assign(1,angToFinal);
//       close = true;
//     }
//   }
//   if (!close) {
//     previousAngToFinals.push_back(angToFinal);
//   }
// }

double MoveToCoordinate::Limit(double value, double limit) {
  if (value < -abs(limit))
    return -abs(limit);
  else if (value > abs(limit))
    return abs(limit);
  else
    return value;
}

double MoveToCoordinate::TurnPID() {
  angleError = ((angToFinal / 180) / cyclePerSecond);
  totalAngleError += angleError;
  if (angleError == 0)
    totalAngleError = 0;
  
  double p = 0.017;
  double i = 0.002;

  if (totalAngleError > (2 * baseSpeed / i))
    totalAngleError = 0;

  return Limit(((p * angToFinal) + (i * totalAngleError)), 2*baseSpeed);
}

void MoveToCoordinate::Set(std::vector<double>pidValues) {
  driveValues = pidValues;
}

double MoveToCoordinate::DrivePID() {
  distanceError = (distance / cyclePerSecond)  * (1 - 2 * (abs(angToFinal) > 90));
  totalDistanceError += distanceError;
  if (distanceError == 0)
    totalDistanceError = 0;

  double p = driveValues[0];
  double i = driveValues[1];
  double d = driveValues[2];

  // double p = frc::SmartDashboard::GetNumber("DriveP: ", 0.245);
  // double i = frc::SmartDashboard::GetNumber("DriveI: ", 0.002);
  // double d = frc::SmartDashboard::GetNumber("DriveD: ", 0.002);

  if ((p * distanceError) > baseSpeed)
    totalDistanceError = 0;
  
  double errorChange = distanceError - previousDistanceError;
  previousDistanceError = distanceError;

  frc::SmartDashboard::PutNumber("distanceError", distanceError);
  return Limit(((p * distanceError) + (i * totalDistanceError) + (d * errorChange)), baseSpeed);
}

bool MoveToCoordinate::HasOscillated() {
  if (driveSpeed < 0) {
    hasOscillated = true;
  }
  return hasOscillated;
}

// Called repeatedly when this Command is scheduled to run
void MoveToCoordinate::Execute() {
  xCurrent = RobotContainer::navigation->GetCoordinatePosition().first;
  yCurrent = RobotContainer::navigation->GetCoordinatePosition().second;


  //Converts final coordinates into angle from robot and subtracts it from current angle.
  angToFinal = RobotContainer::navigation->AngleToPoint(xFinal,yFinal);
  
  //Distance formula between current point and destination point.
  distance = sqrt((xFinal - xCurrent) * (xFinal - xCurrent) + (yFinal - yCurrent) * (yFinal - yCurrent));
  
  frc::SmartDashboard::PutNumber("firstTurn", movementStage);

  if (movementStage == 0) {
    totalAngleError = 0;
    totalDistanceError = 0;
    previousDistanceError = 0;
    if (turnToAngle == nullptr)
        turnToAngle = std::make_unique<TurnToAngle>();

    if (turnToAngle->GetIsFinished()) {
        movementStage = 1;
        turnToAngle->Cancel();
        turnToAngle.reset();
    }
    else if (!turnToAngle->IsScheduled()) {
        turnToAngle->SetAngle(angToFinal);
        turnToAngle->Schedule();
    }
  }
  else if (movementStage == 1) {
    if (distance < 0.5)
        turnSpeed = 0;
    else
        turnSpeed = TurnPID();
    driveSpeed = DrivePID();

    frc::SmartDashboard::PutNumber("driveSpeed", driveSpeed);
    frc::SmartDashboard::PutNumber("turnSpeed", turnSpeed);

    if (turnSpeed < 0) {
      leftPower = driveSpeed - abs(turnSpeed);
      rightPower = driveSpeed;
    }
    else {
      leftPower = driveSpeed;
      rightPower = driveSpeed - abs(turnSpeed);
    }

    // RobotContainer::drivetrain->DriveUsingSpeeds(leftPower,rightPower);

    frc::SmartDashboard::PutNumber("leftPower", leftPower);
    frc::SmartDashboard::PutNumber("rightPower", rightPower);

    averageLeft.push_back(leftPower);
    if (averageLeft.size() > 4) {
      averageLeft.erase(averageLeft.begin());
    }
    averageRight.push_back(rightPower);
    if (averageRight.size() > 4) {
      averageRight.erase(averageRight.begin());
    }

    double pastLeftPowerTotal;
    double pastRightPowerTotal;

    for (unsigned i = 0; i < averageLeft.size(); i++) {
      pastLeftPowerTotal += averageLeft[i];
      pastRightPowerTotal += averageRight[i];
    }
    pastLeftPowerTotal /= 4;
    pastRightPowerTotal /= 4;

    Drivetrain::leftPrimarySpark->Set(-leftPower);
    Drivetrain::rightPrimarySpark->Set(rightPower);



    frc::SmartDashboard::PutNumber("leftPower", leftPower);
    frc::SmartDashboard::PutNumber("rightPower", rightPower);
    Robot::logger->LoadDataToFile("leftPower", Drivetrain::leftPrimarySpark->Get());
    Robot::logger->LoadDataToFile("rightPower", Drivetrain::rightPrimarySpark->Get());
  }
  
  frc::SmartDashboard::PutNumber("distance", distance);
  frc::SmartDashboard::PutNumber("turnIsScheduled", turnToAngle->IsScheduled());


//   Robot::logger->LoadDataToFile("logFile.txt", "angToFinal", angToFinal);
//   Robot::logger->LoadDataToFile("logFile.txt", "movementSpeed", movementStage);
  if (abs(distance) < 0.9) {
    finishCounter++;
  }
  else {
    finishCounter = 0;
  }
}  

// Called once the command ends or is interrupted.
void MoveToCoordinate::End(bool interrupted) {
  frc::SmartDashboard::PutBoolean("hasEnded", true);
  RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
  Drivetrain::leftPrimarySpark->StopMotor();
  Drivetrain::rightPrimarySpark->StopMotor();

  turnToAngle = std::make_unique<TurnToAngle>(origAngleToFinal);
  turnToAngle->Schedule();

//   movementStage = 2;
//   frc::SmartDashboard::PutNumber("firstTurn", movementStage);
}

// Returns true when the command should end.
bool MoveToCoordinate::IsFinished() {
  if (finishCounter > 30) {
    return true;
  }
  else {
    return false;
  }
}