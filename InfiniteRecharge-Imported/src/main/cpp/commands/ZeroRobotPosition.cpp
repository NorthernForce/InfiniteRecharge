/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ZeroRobotPosition.h"

ZeroRobotPosition::ZeroRobotPosition() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ZeroRobotPosition::Initialize() {
  RobotContainer::navigation->ZeroPosition();
}

// Called repeatedly when this Command is scheduled to run
void ZeroRobotPosition::Execute() {}

// Called once the command ends or is interrupted.
void ZeroRobotPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool ZeroRobotPosition::IsFinished() { return true; }
