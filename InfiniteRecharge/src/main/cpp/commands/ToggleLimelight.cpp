// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ToggleLimelight.h"
#include "commands/TurnToAngle.h"
#include <frc2/command/Command.h>
#include <frc2/command/ScheduleCommand.h>
#include "ctre/Phoenix.h"
#include "RobotContainer.h"
#include <iostream>

ToggleLimelight::ToggleLimelight() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::limelight.get());
}

// Called when the command is initially scheduled.
void ToggleLimelight::Initialize() {
 currentLimeMode = RobotContainer::limelight->GetNumberFromTable("ledMode", 0);
}

// Called repeatedly when this Command is scheduled to run
void ToggleLimelight::Execute() {
  if(currentLimeMode == 1) {
    RobotContainer::limelight->PutNumberToTable("ledMode", 3);
  } if(currentLimeMode == 3) {
    RobotContainer::limelight->PutNumberToTable("ledMode", 1);
  }
}

// Called once the command ends or is interrupted.
void ToggleLimelight::End(bool interrupted) {}

// Returns true when the command should end.
bool ToggleLimelight::IsFinished() {
  if(currentLimeMode != RobotContainer::limelight->GetNumberFromTable("ledMode", 0)) {
    return true;
  } else {
    return false;
  }
}
