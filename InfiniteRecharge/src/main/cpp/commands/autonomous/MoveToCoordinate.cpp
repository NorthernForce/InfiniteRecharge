/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Version 0.20

#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/TurnToAngle.h"
#include <memory>
#include <cmath>

MoveToCoordinate::MoveToCoordinate(int xPos, int yPos, double speed) {
  xFinal = xPos;
  yFinal = yPos;
  baseSpeed = speed;
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
  turnSpeed = 1 + (int)(angToFinal > 3) + 2 * (int)(angToFinal > 5) + (int)(angToFinal > 7);

  //Distance formula between current point and destination point.
  distance = sqrt((xFinal - xCurrent) * (xFinal - xCurrent) + (yFinal - yCurrent) * (yFinal - yCurrent));

  //Outputs a value that changes how quickly the robot drives
  // distanceSpeed = .1 * (int)(distance > 0) + .1 * (int)(distance >= 1) + .3 * (int)(distance >= 6) + .5 * (int)(distance >= 12);
  distanceSpeed = 1;

  rightPower = baseSpeed;
  leftPower = baseSpeed;

  if (abs(angToFinal) > 10) {
    //Turn
    if (angToFinal < 0) {
      //Turn left
      leftPower = -baseSpeed;
    }
    else {
      //Turn right
      rightPower = -baseSpeed;
    }
  }
  else if (abs(angToFinal) > 2) {
    //Drive with corrections
    if (angToFinal < 0) {
      //Corrections to the left
      leftPower = baseSpeed / turnSpeed;
    }
    else {
      //Corrections to the right
      rightPower = baseSpeed / turnSpeed;
    }
  }

  RobotContainer::drivetrain->DriveUsingSpeeds(leftPower,rightPower);
  frc::SmartDashboard::PutNumber("leftPower",leftPower);
  frc::SmartDashboard::PutNumber("rightPower",rightPower);
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