/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/InFrontOfFoesTrench.h"
#include "RobotContainer.h"

InFrontOfFoesTrench::InFrontOfFoesTrench() {
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());
}

// Called when the command is initially scheduled.
void InFrontOfFoesTrench::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void InFrontOfFoesTrench::Execute() {}

// Called once the command ends or is interrupted.
void InFrontOfFoesTrench::End(bool interrupted) {}

// Returns true when the command should end.
bool InFrontOfFoesTrench::IsFinished() { return false; }
