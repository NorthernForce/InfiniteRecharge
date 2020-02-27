/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/InFrontOfOurTrench.h"
#include "RobotContainer.h"

InFrontOfOurTrench::InFrontOfOurTrench() {
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());
}

// Called when the command is initially scheduled.
void InFrontOfOurTrench::Initialize() {
  turnToAngle.reset(new TurnToAngle(180));
  RobotContainer::intake->SetArmDown();
  RobotContainer::drivetrain->DriveInInches(0.5, 0.5, 144);
  RobotContainer::intake->SetArmUp();
}

// Called repeatedly when this Command is scheduled to run
void InFrontOfOurTrench::Execute() {}

// Called once the command ends or is interrupted.
void InFrontOfOurTrench::End(bool interrupted) {}

// Returns true when the command should end.
bool InFrontOfOurTrench::IsFinished() { return false; }
