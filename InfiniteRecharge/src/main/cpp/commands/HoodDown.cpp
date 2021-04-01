// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/HoodDown.h"
#include "ctre/Phoenix.h"
#include "RobotContainer.h"

HoodDown::HoodDown() {
  // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(RobotContainer::shooter.get());

}

// Called when the command is initially scheduled.
void HoodDown::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HoodDown::Execute() {
  RobotContainer::shooter->SetHoodSpeed(.8);
}

// Called once the command ends or is interrupted.
void HoodDown::End(bool interrupted) {
    RobotContainer::shooter->SetHoodSpeed(0);
}

// Returns true when the command should end.
bool HoodDown::IsFinished() {
  return false;
}
