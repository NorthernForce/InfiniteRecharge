/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakePowerCell.h"

IntakePowerCell::IntakePowerCell() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void IntakePowerCell::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {
  RobotContainer::intake->TakeIn();
}

// Called once the command ends or is interrupted.
void IntakePowerCell::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakePowerCell::IsFinished() { return false; } //need to set this to true? also might need to set finished when have five power cells
