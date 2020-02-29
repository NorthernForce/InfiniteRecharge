/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunIntakeMotor.h"
#include <iostream>

RunIntakeMotor::RunIntakeMotor() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void RunIntakeMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntakeMotor::Execute() {
    RobotContainer::intake->TakeInPowerCell();
    RobotContainer::intake->RunConveyor();
}

// Called once the command ends or is interrupted.
void RunIntakeMotor::End(bool interrupted) {
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool RunIntakeMotor::IsFinished() { return false; }
