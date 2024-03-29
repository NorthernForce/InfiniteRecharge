/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakePowerCell.h"
#include "RobotContainer.h"
#include <iostream>

const double conveyorRunSpeed = -0.50;
const double conveyorBackwardSpeed = 0.4;

IntakePowerCell::IntakePowerCell() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakePowerCell::Initialize() {
  emptyPosition = RobotContainer::intake->GetFirstEmptyPosition();
  conveyorBackwardsCounter = 0;
  rumbleCounter = 0;
  fourReached = false; //changed from fiveReached
  emptyPositionTriggered = false;
  oneTriggered = false;
  badIntake = false;
  zeroTriggered = false;
}

//***************************************************************************
////TODO: NEED to check if Pos. 4 is empty before starting Intake!!
//****************************************************************************
void IntakePowerCell::Execute() {
  
  std::cout << "Empty Position is " << emptyPosition <<  "\n";
  std::cout << "Empty Position Triggered: " << emptyPositionTriggered << "\n";
  std::cout << "Pos 1 Triggered is " << badIntake <<  "\n";
  std::cout << "Bad intake is " << badIntake <<  "\n";
  std::cout << "Pos 0 Triggered: " << zeroTriggered << "\n";

  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT) {
    std::cout << "Empty Position " << emptyPosition <<  " full\n";
  }
  else {
    std::cout << "Empty Position " << emptyPosition <<  " empty\n";
  }

  //changed from 5 to 4
  if (RobotContainer::intake->GetInventory(4) == Intake::StorageState::PRESENT) {
    RobotContainer::intake->StopConveyor();
  }

  else {
   
    //run conveyor and intake to take in power cell
    RobotContainer::intake->TakeInPowerCell();
    if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT && emptyPositionTriggered == false) {
      RobotContainer::intake->ConveyorSetSpeed(-.3);
    }

  }
  //tag to keep the conveyor from oscillating at four (changed from 5)
  if (RobotContainer::intake->GetInventory(4) == Intake::StorageState::PRESENT) {
    fourReached = true; //changed from fiveReached
  }

  //makes it so the counter will only be reset if the ball is no longer in 4 (changed from 5)
  if (RobotContainer::intake->GetInventory(4) == Intake::StorageState::EMPTY) {
    conveyorBackwardsCounter = 0;
  }

  //makes controller rumble to tell driver there is a ball in five
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT && rumbleCounter <= 9) {
   RobotContainer::oi->SetControllerRumble(OI::driverController.get(), 1, true);
   rumbleCounter++;
  }  
  else {
    RobotContainer::oi->SetControllerRumble(OI::driverController.get(), 0, true);
  }

  //sees if 0 has been triggered
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT) {
    zeroTriggered = true;
  }

  // sees if one has been triggered
  if (RobotContainer::intake->GetInventory(1) == Intake::StorageState::PRESENT) {
    oneTriggered = true;
  }

   //sees if the emptyPosition has been triggered
  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT && oneTriggered == true) {
    emptyPositionTriggered = true;
  }

  //determines if there was a bad intake and then backs up conveyor
  if (emptyPositionTriggered == true && RobotContainer::intake->GetInventory(1) == Intake::StorageState::EMPTY && zeroTriggered == true && RobotContainer::intake->GetInventory(0) == Intake::StorageState::EMPTY) {
    badIntake = true;
    RobotContainer::intake->ConveyorSetSpeed(conveyorBackwardSpeed);
  }


}

// Called once the command ends or is interrupted.
void IntakePowerCell::End(bool interrupted) {
  RobotContainer::oi->SetControllerRumble(OI::driverController.get(), 0, true);
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool IntakePowerCell::IsFinished() {
  //makes sure power cell has advanced to empty position and there aren't any gaps before stopping
  if (emptyPositionTriggered == true && RobotContainer::intake->GetInventory(1) == Intake::StorageState::PRESENT)
    return true;
  else
    return false; 
}
