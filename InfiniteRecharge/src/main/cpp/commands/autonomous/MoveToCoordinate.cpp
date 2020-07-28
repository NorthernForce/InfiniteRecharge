/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Version 11.0

#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/TurnToAngle.h"
#include <memory>

MoveToCoordinate::MoveToCoordinate(int xPos, int yPos, double speed) {
  xFinal = xPos;
  yFinal = yPos;
  baseSpeed = speed;
}

// Called when the command is initially scheduled.
void MoveToCoordinate::Initialize() {
  turnToAngle = std::make_shared<TurnToAngle>();
}

// Called repeatedly when this Command is scheduled to run
void MoveToCoordinate::Execute() {
  angToFinal = (-180 * (xFinal<xCurrent)+atan(abs((yFinal-yCurrent)/(xFinal-xCurrent))) / Constants::degreesToRadians) * (1 - 2 * (xFinal<xCurrent)) * (1 - 2 * (yFinal>yCurrent));
  frc::SmartDashboard::PutNumber("angleToFinal", angToFinal);

  distance = sqrt ((xFinal-xCurrent)*(xFinal-xCurrent) + (yFinal-yCurrent)*(yFinal-yCurrent));
  frc::SmartDashboard::PutNumber("distance", distance);

  angleDifference = angToFinal - RobotContainer::imu->GetRotation();
  frc::SmartDashboard::PutNumber("AngleDifference", angleDifference);

  frc::SmartDashboard::PutNumber("turnIsScheduled", turnToAngle->IsScheduled());
  if (!turnToAngle->IsScheduled()) {
    xCurrent = RobotContainer::navigation->GetCoordinatePosition().first;
    yCurrent = RobotContainer::navigation->GetCoordinatePosition().second;
    //Converts final coordinates into angle from robot and subtracts it from current angle

    //Outputs a value that changes how quickly the robot drives
    distanceSpeed = .1 * (distance > 0) + .1 * (distance >= 1) + .3 * (distance >= 6) + .5 * (distance >= 12);
    //If robot is more than 10 degrees off -> Turns directly to target. Otherwise it will try to correct and drive.
    if (abs(angleDifference) > 10) {
      turnToAngle->SetAngle(angleDifference);
      turnToAngle->Schedule();
    }
    else {
      distance = 0;
      leftPower = distanceSpeed * baseSpeed;
      rightPower = distanceSpeed * baseSpeed;
      RobotContainer::drivetrain->DriveUsingSpeeds(leftPower,rightPower);
      frc::SmartDashboard::PutNumber("leftPower",leftPower);
      frc::SmartDashboard::PutNumber("rightPower",rightPower);
    }
  }  
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
