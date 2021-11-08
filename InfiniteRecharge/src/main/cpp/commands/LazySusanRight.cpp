// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LazySusanRight.h"
#include "ctre/Phoenix.h"
#include "RobotContainer.h"

LazySusanRight::LazySusanRight() {}

// Called when the command is initially scheduled.
void LazySusanRight::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LazySusanRight::Execute() {
    std::cout << "running right\n";
    RobotContainer::shooter->SetSusanSpeed(0.8);
}

// Called once the command ends or is interrupted.
void LazySusanRight::End(bool interrupted) {
    RobotContainer::shooter->SetSusanSpeed(0);
}

// Returns true when the command should end.
bool LazySusanRight::IsFinished() {
  return false;
}
