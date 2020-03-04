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

}

// Called repeatedly when this Command is scheduled to run
void ToggleArm::Execute() {
  auto controller = RobotContainer::oi->manipulatorController;
  if (RobotContainer::intake->GetArmState() == Intake::ArmState::armIsUp) {
    RobotContainer::intake->SetArmDown();
    if (RobotContainer::intake->GetArmState() == Intake::ArmState::armIsUp)
      RobotContainer::oi->SetControllerRumble(controller.get(), 1);
  }
  else {
    RobotContainer::intake->SetArmUp();
    if (RobotContainer::intake->GetArmState() == Intake::ArmState::armIsDown)
      RobotContainer::oi->SetControllerRumble(controller.get(), 1);
  }
}

// Called once the command ends or is interrupted.
void ToggleArm::End(bool interrupted) {}

// Returns true when the command should end.
bool ToggleArm::IsFinished() { return false; }
