/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualIntake.h"

ManualIntake::ManualIntake() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ManualIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualIntake::Execute() {
  RobotContainer::intake->TakeInPowerCell();
}

// Called once the command ends or is interrupted.
void ManualIntake::End(bool interrupted) {
  RobotContainer::intake->Stop();
}

// Returns true when the command should end.
bool ManualIntake::IsFinished() { return false; }
