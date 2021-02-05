/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ReverseConveyor.h"
#include "RobotContainer.h"

ReverseConveyor::ReverseConveyor() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ReverseConveyor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ReverseConveyor::Execute() {
  RobotContainer::intake->ConveyorSetSpeed(-.3);
}

// Called once the command ends or is interrupted.
void ReverseConveyor::End(bool interrupted) {
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool ReverseConveyor::IsFinished() { return false; }
