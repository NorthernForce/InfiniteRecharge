/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualShooter.h"

ManualShooter::ManualShooter() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void ManualShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualShooter::Execute() {
  RobotContainer::shooter->SetRawSpeed(0.5);
}

// Called once the command ends or is interrupted.
void ManualShooter::End(bool interrupted) {
  RobotContainer::shooter->SetRawSpeed(0.0);
}

// Returns true when the command should end.
bool ManualShooter::IsFinished() { return false; }
