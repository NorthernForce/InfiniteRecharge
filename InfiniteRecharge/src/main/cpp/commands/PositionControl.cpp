/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionControl.h"
#include "RobotContainer.h"

PositionControl::PositionControl() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::wackyWheel.get());
}

// Called when the command is initially scheduled.
void PositionControl::Initialize() {  
  RobotContainer::wackyWheel->Rotate(4);
}

// Called repeatedly when this Command is scheduled to run
void PositionControl::Execute() {}

// Called once the command ends or is interrupted.
void PositionControl::End(bool interrupted) {}

// Returns true when the command should end.
bool PositionControl::IsFinished() { return false; }
