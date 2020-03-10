/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IncreaseShooterRPM.h"
#include "RobotContainer.h"

IncreaseShooterRPM::IncreaseShooterRPM() {}

// Called when the command is initially scheduled.
void IncreaseShooterRPM::Initialize() {
  int currentRPM = RobotContainer::shooter->GetCurrentRPM();
  int targetRPM = currentRPM + 250;
  RobotContainer::shooter->SetTargetRPM(targetRPM);
}

// Called repeatedly when this Command is scheduled to run
void IncreaseShooterRPM::Execute() {}

// Called once the command ends or is interrupted.
void IncreaseShooterRPM::End(bool interrupted) {}

// Returns true when the command should end.
bool IncreaseShooterRPM::IsFinished() { return true; }