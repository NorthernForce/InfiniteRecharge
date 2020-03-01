/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AimShooterUp.h"

AimShooterUp::AimShooterUp() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void AimShooterUp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AimShooterUp::Execute() {
  RobotContainer::shooter->ShooterUp();
}

// Called once the command ends or is interrupted.
void AimShooterUp::End(bool interrupted) {}

// Returns true when the command should end.
bool AimShooterUp::IsFinished() { return false; }
