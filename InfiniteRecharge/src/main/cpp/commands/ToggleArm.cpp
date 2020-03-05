/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleArm.h"

ToggleArm::ToggleArm() {
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ToggleArm::Initialize() {
  RobotContainer::intake->SetArm(0.5);
}

// Called repeatedly when this Command is scheduled to run
void ToggleArm::Execute() {
  currentEncoderPos = RobotContainer::intake->GetArmPosition();
  if (currentEncoderPos != previousEncoderPos)
    RobotContainer::intake->SetArm(0);
  else
    RobotContainer::intake->SetArm(0.5);
  previousEncoderPos = currentEncoderPos;
}

// Called once the command ends or is interrupted.
void ToggleArm::End(bool interrupted) {
  RobotContainer::intake->SetArm(0);
}

// Returns true when the command should end.
bool ToggleArm::IsFinished() { return false; }
