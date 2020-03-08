/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakePowerCell.h"
#include "OI.h"
#include "RobotContainer.h"
#include <iostream>

IntakePowerCell::IntakePowerCell() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakePowerCell::Initialize() {
  emptyPosition = RobotContainer::intake->GetFirstEmptyPosition();
  zeroHasBeenTriggered = false;
}

// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {
  RobotContainer::intake->TakeInPowerCell();
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT) { //&& RobotContainer::intake->powerCellCount <= 5
    RobotContainer::intake->ConveyorSetSpeed(-0.45);
    zeroHasBeenTriggered = true;
    //std::cout << "in if statement for conveyor\n";
  }
  // if (RobotContainer::intake->GetPowerCellCount() >= 5) {
  //   RobotContainer::oi->SetControllerRumble(OI::driverController.get(), 1, true);
  //   RobotContainer::intake->Stop();
  //   RobotContainer::intake->StopConveyor();
  // }
  else if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT) {
    RobotContainer::intake->StopConveyor();
  }
}

// Called once the command ends or is interrupted.
void IntakePowerCell::End(bool interrupted) {
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool IntakePowerCell::IsFinished() {
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::EMPTY && zeroHasBeenTriggered == true)
    return true;
  else
    return false; 
}
