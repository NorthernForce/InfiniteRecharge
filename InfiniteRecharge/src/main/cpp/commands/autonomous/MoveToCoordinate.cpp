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

std::unique_ptr<Logger> Robot::logger;

MoveToCoordinate::MoveToCoordinate(int xPos, int yPos, double speed):baseSpeed(speed) {
  turnToAngle = std::make_unique<TurnToAngle>();
  xFinal = xPos;
  yFinal = yPos;
  movementStage = 0;
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
  if (value < - abs(limit))
    return -abs(limit);
  else if (value > abs(limit))
    return abs(limit);
  else
    return value;
}

double MoveToCoordinate::TurnPID() {
  angleError = (angToFinal / 180) / cyclePerSecond;
  totalAngleError += angleError;
  if (angleError == 0)
    totalAngleError = 0;
  
  double p = 1.6;
  double i = 0.02;

  if (totalAngleError > (2 * baseSpeed / i))
    totalAngleError = 0;

  return Limit(((p * angToFinal) + (i * totalAngleError)), 2*baseSpeed);
}

double MoveToCoordinate::DrivePID() {
  distanceError = distance / cyclePerSecond;
  totalDistanceError += distanceError;
  if (distanceError == 0)
    totalDistanceError = 0;

  double p = 1.6;
  double i = 0.6;
  double d = 0.001;

  if ((p * distanceError) > baseSpeed)
    totalDistanceError = 0;
  
  double errorChange = distanceError - previousDistanceError;
  previousDistanceError = distanceError;

  return Limit(((p * distanceError) + (i * totalDistanceError) + (d * errorChange)), baseSpeed);
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
    if (turnToAngle->GetIsFinished()) {
        movementStage = 1;
        turnToAngle.reset(new TurnToAngle);
    }
    else if (!turnToAngle->IsScheduled()) {
        turnToAngle->SetAngle(angToFinal);
        turnToAngle->Schedule();
    }
  }
  else if (movementStage == 1) {
    turnSpeed = TurnPID();
    driveSpeed = DrivePID();
    if (turnSpeed < 0) {
      leftPower = driveSpeed - abs(turnSpeed);
      rightPower = driveSpeed;
    }
    else {
      leftPower = driveSpeed;
      rightPower = driveSpeed - abs(turnSpeed);
    }
  }
  //   rightPower = baseSpeed;
  //   leftPower = baseSpeed;

  //   if (abs(angToFinal) > 3) {
  //     movementStage = 0;
  //   }
  // }

  // if (abs(leftPower) > baseSpeed) {
  //   leftPower = baseSpeed * (1 - 2 * (int)(leftPower < 0));
  // }
  // if (abs(rightPower) > baseSpeed) {
  //   rightPower = baseSpeed * (1 - 2 * (int)(rightPower < 0));

  RobotContainer::drivetrain->DriveUsingSpeeds(leftPower,rightPower);
  
  frc::SmartDashboard::PutNumber("leftPower", Drivetrain::leftPrimarySpark->Get());
  frc::SmartDashboard::PutNumber("rightPower", Drivetrain::rightPrimarySpark->Get());
  frc::SmartDashboard::PutNumber("distance", distance);
  frc::SmartDashboard::PutNumber("turnIsScheduled", turnToAngle->IsScheduled());
  frc::SmartDashboard::PutNumber("driveSpeed", driveSpeed);
  frc::SmartDashboard::PutNumber("turnSpeed", turnSpeed);


//   Robot::logger->LoadDataToFile("logFile.txt", "angToFinal", angToFinal);
//   Robot::logger->LoadDataToFile("logFile.txt", "movementSpeed", movementStage);
}  

// Called once the command ends or is interrupted.
void MoveToCoordinate::End(bool interrupted) {
  RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
//   movementStage = 2;
//   frc::SmartDashboard::PutNumber("firstTurn", movementStage);
}

// Returns true when the command should end.
bool MoveToCoordinate::IsFinished() {
  if (abs(distance) < 0.45) {
    return true;
  }
  else {
    return false;
  }
}