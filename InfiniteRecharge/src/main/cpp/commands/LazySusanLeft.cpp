// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LazySusanLeft.h"
#include "ctre/Phoenix.h"
#include "RobotContainer.h"

LazySusanLeft::LazySusanLeft() {
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void LazySusanLeft::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LazySusanLeft::Execute() {
    RobotContainer::shooter->SetSusanSpeed(-0.8);
}

// Called once the command ends or is interrupted.
void LazySusanLeft::End(bool interrupted) {
    RobotContainer::shooter->SetSusanSpeed(0);
}

// Returns true when the command should end.
bool LazySusanLeft::IsFinished() {
  return false;
}
