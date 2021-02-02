/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AimShooterDown.h"

AimShooterDown::AimShooterDown() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void AimShooterDown::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AimShooterDown::Execute() {
  RobotContainer::shooter->ShooterDown();
}

// Called once the command ends or is interrupted.
void AimShooterDown::End(bool interrupted) {}

// Returns true when the command should end.
bool AimShooterDown::IsFinished() { return false; }
