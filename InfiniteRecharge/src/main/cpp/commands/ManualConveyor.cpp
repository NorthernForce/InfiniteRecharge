/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualConveyor.h"

ManualConveyor::ManualConveyor() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ManualConveyor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualConveyor::Execute() {
  RobotContainer::intake->RunConveyor();
}

// Called once the command ends or is interrupted.
void ManualConveyor::End(bool interrupted) {
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool ManualConveyor::IsFinished() { return false; }
