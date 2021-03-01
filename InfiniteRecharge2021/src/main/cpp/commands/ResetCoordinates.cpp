/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "commands/ResetCoordinates.h"

ResetCoordinates::ResetCoordinates() {
  AddRequirements(RobotContainer::cameraMount.get());
  AddRequirements(RobotContainer::navigation.get());
}
// Called when the command is initially scheduled.
void ResetCoordinates::Initialize() {
  RobotContainer::cameraMount->Pan(0);
  RobotContainer::cameraMount->Tilt(85);
  RobotContainer::navigation->ResetPosition();  
}

// Called repeatedly when this Command is scheduled to run
void ResetCoordinates::Execute() {}

// Called once the command ends or is interrupted.
void ResetCoordinates::End(bool interrupted) {}

// Returns true when the command should end.
bool ResetCoordinates::IsFinished() { return false; }
