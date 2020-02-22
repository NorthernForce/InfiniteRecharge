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
void ToggleArm::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ToggleArm::Execute() {
  if (RobotContainer::intake->GetArmState() == Intake::ArmState::armIsUp) {
    if (RobotContainer::intake->ArmDown() == false) {
      ////TODO: make controller rumble
    }
  }
  else {
    if (RobotContainer::intake->ArmUp() == false) {
      ////TODO: make controller rumble
    }
  }
}

// Called once the command ends or is interrupted.
void ToggleArm::End(bool interrupted) {}

// Returns true when the command should end.
bool ToggleArm::IsFinished() { return false; }
