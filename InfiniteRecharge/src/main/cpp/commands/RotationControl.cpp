/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RotationControl.h"
#include "RobotContainer.h"

RotationControl::RotationControl() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::wackyWheel.get());
}

// Called when the command is initially scheduled.
void RotationControl::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RotationControl::Execute() {
  RobotContainer::wackyWheel->RotationControl();
}

// Called once the command ends or is interrupted.
void RotationControl::End(bool interrupted) {}

// Returns true when the command should end.
bool RotationControl::IsFinished() { return false; }
