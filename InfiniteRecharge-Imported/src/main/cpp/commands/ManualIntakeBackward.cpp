/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualIntakeBackward.h"

ManualIntakeBackward::ManualIntakeBackward() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ManualIntakeBackward::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualIntakeBackward::Execute() {
  RobotContainer::intake->PushOutPowerCell();
}

// Called once the command ends or is interrupted.
void ManualIntakeBackward::End(bool interrupted) {
  RobotContainer::intake->Stop();
}

// Returns true when the command should end.
bool ManualIntakeBackward::IsFinished() { return false; }
