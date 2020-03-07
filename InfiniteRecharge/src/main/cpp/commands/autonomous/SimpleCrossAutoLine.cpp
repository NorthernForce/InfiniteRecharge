/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/SimpleCrossAutoLine.h"
#include "RobotContainer.h"

SimpleCrossAutoLine::SimpleCrossAutoLine() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void SimpleCrossAutoLine::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SimpleCrossAutoLine::Execute() {
  RobotContainer::drivetrain->SimpleDriveWithEncoder(5.899999);
}

// Called once the command ends or is interrupted.
void SimpleCrossAutoLine::End(bool interrupted) {}

// Returns true when the command should end.
bool SimpleCrossAutoLine::IsFinished() { return false; }