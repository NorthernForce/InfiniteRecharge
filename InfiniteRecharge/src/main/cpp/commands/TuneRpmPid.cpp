/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TuneRpmPid.h"
#include "RobotContainer.h"

TuneRpmPid::TuneRpmPid() {
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void TuneRpmPid::Initialize() {
  // RobotContainer::shooter->TuneRpmPid_P(); // removed for testing
}

// Called repeatedly when this Command is scheduled to run
void TuneRpmPid::Execute() {}

// Called once the command ends or is interrupted.
void TuneRpmPid::End(bool interrupted) {}

// Returns true when the command should end.
bool TuneRpmPid::IsFinished() { return true; }
