/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"

MoveToCoordinate::MoveToCoordinate(int xPos, int yPos, double speed) {
  AddRequirements(RobotContainer::drivetrain.get());
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
  //Converts final coordinates into angle from robot and subtracts it from current angle
  angToFinal = RobotContainer::imu->GetRotation() - (180*(xFinal < yCurrent) - 
  (tanh(abs(yFinal/xFinal))/Constants::degreesToRadians)) * (1 - 2 * (xFinal < xCurrent));
  //Outputs a value that changes how sharply the robot turns
  turnSpeed = -.1 * (abs(angToFinal) >= 1) - .1 * (abs(angToFinal) >= 5) - .3 * 
  (abs(angToFinal) >= 45) - .5 * (abs(angToFinal) >= 90) - (abs(angToFinal) > 150);

  distance = sqrt ((xFinal-xCurrent)*(xFinal-xCurrent) + (yFinal-yCurrent)*(yFinal-yCurrent));
  //Outputs a value that changes how quickly the robot drives
  distanceSpeed = .2 * (distance >= 1) + .3 * (distance >= 6) + .5 * (distance >= 12);
  if (angToFinal <= 0) { //Reads true if the robot needs to turn left or go straight
    rightPower = distanceSpeed * baseSpeed;
    leftPower = (distanceSpeed + turnSpeed) * baseSpeed;
  }
  else {
    rightPower = (distanceSpeed + turnSpeed) * baseSpeed;
    leftPower = distanceSpeed * baseSpeed;
  }
  RobotContainer::drivetrain->DriveUsingSpeeds(leftPower, rightPower);
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
