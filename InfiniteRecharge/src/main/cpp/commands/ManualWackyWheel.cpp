/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualWackyWheel.h"
#include "RobotContainer.h"

ManualWackyWheel::ManualWackyWheel() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::wackyWheel.get());
}

// Called when the command is initially scheduled.
void ManualWackyWheel::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualWackyWheel::Execute() {
  RobotContainer::wackyWheel->ManualSpin();
}

// Called once the command ends or is interrupted.
void ManualWackyWheel::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualWackyWheel::IsFinished() { return false; }
