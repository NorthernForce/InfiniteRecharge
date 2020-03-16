/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DecreaseShooterRPM.h"
#include "RobotContainer.h"

DecreaseShooterRPM::DecreaseShooterRPM() {}

// Called when the command is initially scheduled.
void DecreaseShooterRPM::Initialize() {
  int currentRPM = RobotContainer::shooter->GetCurrentRPM();
  int targetRPM = currentRPM - 250;
  RobotContainer::shooter->SetTargetRPM(targetRPM);
}

// Called repeatedly when this Command is scheduled to run
void DecreaseShooterRPM::Execute() {}

// Called once the command ends or is interrupted.
void DecreaseShooterRPM::End(bool interrupted) {}

// Returns true when the command should end.
bool DecreaseShooterRPM::IsFinished() { return true; }
