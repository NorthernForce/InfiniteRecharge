/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Version 12.0

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
void MoveToCoordinate::Initialize() {
  turnToAngle = std::make_shared<TurnToAngle>();
}

// Called repeatedly when this Command is scheduled to run
void MoveToCoordinate::Execute() {
  xCurrent = RobotContainer::navigation->GetCoordinatePosition().first;
  yCurrent = RobotContainer::navigation->GetCoordinatePosition().second;

  //Converts final coordinates into angle from robot and subtracts it from current angle.
  angToFinal = -(atan((yFinal-yCurrent)/(xFinal-xCurrent)) / Constants::degreesToRadians - (int(RobotContainer::imu->GetRotation()) % 360)) +
  //Modifies atan output for (+-)0° - 180° instead of 0° - 90° 
  (180 * (xFinal<xCurrent) * (1 - 2 * (yFinal>yCurrent)));
  
  frc::SmartDashboard::PutNumber("angleToFinal", angToFinal);

  //Distance formula between current point and destination point.
  distance = sqrt ((xFinal-xCurrent)*(xFinal-xCurrent) + (yFinal-yCurrent)*(yFinal-yCurrent));
  frc::SmartDashboard::PutNumber("distance", distance);

  frc::SmartDashboard::PutNumber("turnIsScheduled", turnToAngle->IsScheduled());
  if (!turnToAngle->IsScheduled()) {

    //Outputs a value that changes how quickly the robot drives
    distanceSpeed = .1 * (distance > 0) + .1 * (distance >= 1) + .3 * (distance >= 6) + .5 * (distance >= 12);
    //If robot is more than 10 degrees off -> Turns directly to target. Otherwise it will try to correct and drive.
    if (abs(angToFinal) > 10) {
      turnToAngle->SetAngle(angToFinal);
      turnToAngle->Schedule();
    }
    else {
      //(angToFinal/k); k scales correction while driving. k -> 0; correction increases.
      distanceSpeed = distanceSpeed - (abs(angToFinal/15) * distanceSpeed);
      leftPower = (distanceSpeed - (angToFinal/15)) * baseSpeed;
      rightPower = (distanceSpeed + (angToFinal/15)) * baseSpeed;
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
