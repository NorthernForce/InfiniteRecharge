/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Version 0.24

#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/TurnToAngle.h"
#include <memory>
#include <cmath>
#include "subsystems/Drivetrain.h"

MoveToCoordinate::MoveToCoordinate(int xPos, int yPos, double speed):baseSpeed(speed) {
  turnToAngle = std::make_shared<TurnToAngle>();
  xFinal = xPos;
  yFinal = yPos;
}

// Called when the command is initially scheduled.
void MoveToCoordinate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveToCoordinate::Execute() {
  xCurrent = RobotContainer::navigation->GetCoordinatePosition().first;
  yCurrent = RobotContainer::navigation->GetCoordinatePosition().second;


  //Converts final coordinates into angle from robot and subtracts it from current angle.
  angToFinal = RobotContainer::navigation->AngleToPoint(xFinal,yFinal);
  
  //Higher number -> Sharper Turn
  // turnSpeed = 1 + (int)(angToFinal > 3) + 2 * (int)(angToFinal > 5) + (int)(angToFinal > 7);

  //Distance formula between current point and destination point.
  distance = sqrt((xFinal - xCurrent) * (xFinal - xCurrent) + (yFinal - yCurrent) * (yFinal - yCurrent));

  //Outputs a value that changes how quickly the robot drives
  // distanceSpeed = .1 * (int)(distance > 0) + .1 * (int)(distance >= 1) + .3 * (int)(distance >= 6) + .5 * (int)(distance >= 12);
  if (abs(angToFinal) < 10) {
    distanceSpeed = 1 - .5 * (int)(distance < 12);
  }

  // Removing Jumps in angle value
  bool close = false;
  for (int i; i < previousAngToFinals.size(); i++) {
    if ((angToFinal < previousAngToFinals[i] + 1) && (angToFinal > previousAngToFinals[i] - 1)) {
      previousAngToFinals.assign(1,angToFinal);
      close = true;
    }
  }
  if (!close) {
    previousAngToFinals.push_back(angToFinal);
  }
  
  frc::SmartDashboard::PutNumber("firstTurn", firstTurn);

  if (int(firstTurn) == 0) {
    if (angToFinal < 0) {
      //Turn left
      leftPower = -1 * baseSpeed;
      rightPower = 1 * baseSpeed;
    }
    else {
      //Turn right
      leftPower = 1 * baseSpeed;
      rightPower = -1 * baseSpeed;
    }
    if (angToFinal < 2) {
      firstTurn = 1;
    }
  }
  else if (int(firstTurn) == 1) {
  // if (true) {
    rightPower = baseSpeed;
    leftPower = baseSpeed;

    if (abs(angToFinal) > 20) {
      if (angToFinal < 0) {
        //Turn left
        leftPower = -1.5 * baseSpeed;
        rightPower = 1.5 * baseSpeed;
      }
      else {
        //Turn right
        leftPower = 1.5 * baseSpeed;
        rightPower = -1.5 * baseSpeed;
      }
    }
    else if (abs(angToFinal) > 10) {
      if (angToFinal < 0) {
        //Corrections to the left
        leftPower = baseSpeed / 4;
      }
      else {
        //Corrections to the right
        rightPower = baseSpeed / 4;
      }
    }
    else if (abs(angToFinal) > 5) {
      if (angToFinal < 0) {
        //Corrections to the left
        leftPower = baseSpeed / 5;
      }
      else {
        //Corrections to the right
        rightPower = baseSpeed / 5;
      }
    }
  }

  RobotContainer::drivetrain->DriveUsingSpeeds(leftPower,rightPower);
  
  frc::SmartDashboard::PutNumber("leftPower", Drivetrain::leftPrimarySpark->Get());
  frc::SmartDashboard::PutNumber("rightPower", Drivetrain::rightPrimarySpark->Get());
  frc::SmartDashboard::PutNumber("distance", distance);
  frc::SmartDashboard::PutNumber("turnIsScheduled", turnToAngle->IsScheduled());
}  

// Called once the command ends or is interrupted.
void MoveToCoordinate::End(bool interrupted) {
  RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
}

// Returns true when the command should end.
bool MoveToCoordinate::IsFinished() {
  if (abs(distance) < 3) {
    return true;
  }
  else {
    return false;
  }
}