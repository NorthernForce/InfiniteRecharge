// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/HoodUp.h"
#include "ctre/Phoenix.h"
#include "RobotContainer.h"

HoodUp::HoodUp() {
  // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void HoodUp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HoodUp::Execute() {
  RobotContainer::shooter->SetHoodSpeed(-.8);
}

// Called once the command ends or is interrupted.
void HoodUp::End(bool interrupted) {
  RobotContainer::shooter->SetHoodSpeed(0);
}

// Returns true when the command should end.
bool HoodUp::IsFinished() {
  return false;
}
