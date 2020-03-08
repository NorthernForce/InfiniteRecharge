/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/createAutonomousCommands/CreateAutoPrintLine.h"
#include "commands/autonomous/AutoPrintLine.h"

CreateAutoPrintLine::CreateAutoPrintLine() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void CreateAutoPrintLine::Initialize() {
  frc2::Command* autonomousCommand = new AutoPrintLine();
	autonomousCommand->Start();
}

// Called repeatedly when this Command is scheduled to run
void CreateAutoPrintLine::Execute() {}

// Called once the command ends or is interrupted.
void CreateAutoPrintLine::End(bool interrupted) {}

// Returns true when the command should end.
bool CreateAutoPrintLine::IsFinished() { return false; }
