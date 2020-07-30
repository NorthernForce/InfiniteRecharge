/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Version 15.1

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
  if ((xFinal - xCurrent) == 0) {
    angToFinal = (-(90) / Constants::degreesToRadians - RobotContainer::imu->GetRotation()) + (180 * (xFinal<xCurrent) * (1 - 2 * (yFinal>yCurrent)));
  }
  else {
    angToFinal = -(atan((yFinal-yCurrent)/(xFinal-xCurrent)) / Constants::degreesToRadians - RobotContainer::imu->GetRotation()) + (180 * (xFinal<xCurrent) * (1 - 2 * (yFinal>yCurrent)));
  }
  
  frc::SmartDashboard::PutNumber("angleToFinal", angToFinal);

  //Distance formula between current point and destination point.
  distance = sqrt ((xFinal-xCurrent)*(xFinal-xCurrent) + (yFinal-yCurrent)*(yFinal-yCurrent));
  frc::SmartDashboard::PutNumber("distance", distance);

  frc::SmartDashboard::PutNumber("turnIsScheduled", turnToAngle->IsScheduled());

   //Outputs a value that changes how quickly the robot drives
   distanceSpeed = .1 * (distance > 0) + .1 * (distance >= 1) + .3 * (distance >= 6) + .5 * (distance >= 12);
   //(angToFinal/k); k scales correction while driving. k -> 0; correction increases.
   distanceSpeed = distanceSpeed - (abs(angToFinal/15) * distanceSpeed);
   leftPower = (distanceSpeed - (angToFinal/15)) * baseSpeed;
   rightPower = (distanceSpeed + (angToFinal/15)) * baseSpeed;
   RobotContainer::drivetrain->DriveUsingSpeeds(leftPower,rightPower);
   frc::SmartDashboard::PutNumber("leftPower",leftPower);
   frc::SmartDashboard::PutNumber("rightPower",rightPower);
}  

// Called once the command ends or is interrupted.
void MoveToCoordinate::End(bool interrupted) {
  RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
}

// Returns true when the command should end.
bool MoveToCoordinate::IsFinished() {
  if (distance < .5) {
    return true;
  }
  else {
    return false;
  }
  
}
