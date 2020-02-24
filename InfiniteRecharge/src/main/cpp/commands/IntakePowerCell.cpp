/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakePowerCell.h"

IntakePowerCell::IntakePowerCell() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakePowerCell::Initialize() {
  IntakePowerCell::emptyPosition = RobotContainer::intake->GetFirstEmptyPosition();
}

// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT) {
     RobotContainer::intake->RunConveyor();
  }
}

// Called once the command ends or is interrupted.
void IntakePowerCell::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakePowerCell::IsFinished() { 
  if (RobotContainer::intake->GetInventory(IntakePowerCell::emptyPosition) == Intake::StorageState::PRESENT) {
    RobotContainer::intake->StopConveyor();
    return true;
  }
  else {
  return false; 
  }
}
