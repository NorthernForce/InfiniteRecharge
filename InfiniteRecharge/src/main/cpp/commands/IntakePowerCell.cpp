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
  fiveReached = false;
  emptyPositionTriggered = false;
 // zeroHasBeenTriggered = false;
}

//***************************************************************************
////TODO: NEED to check if Pos. 5 is empty before starting Intake!!
//****************************************************************************
// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {
  
  std::cout << "Empty Position is " << emptyPosition <<  "\n";
  std::cout << "Empty Position Triggered: " << emptyPositionTriggered << "\n";
  std::cout << "Bad intake is " << badIntake <<  "\n";
  //std::cout << "Pos 5 Triggered: " << fiveReached << "\n";

  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT) {
    std::cout << "Empty Position " << emptyPosition <<  " full\n";
  }
  else {
    std::cout << "Empty Position " << emptyPosition <<  " empty\n";
  }

  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT) {
    RobotContainer::intake->StopConveyor();
  }

/*
  //stops conveyor when power cell has cleared pos 0
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT && conveyorBackwardsCounter <= 2 && fiveReached == false) {

    //controls how long conveyor goes backward for
    if (conveyorBackwardsCounter >= backwardCountLimit) {
      RobotContainer::intake->StopConveyor();
      //conveyorBackwardsCounter = 0;
    }

    //move conveyor backward to try and brake faster 
    if (conveyorBackwardsCounter == 0) {
      RobotContainer::intake->ConveyorSetSpeed(conveyorBackwardSpeed);
    }
    conveyorBackwardsCounter++;
  } 
*/
  else {
   
    //run conveyor and intake to take in power cell
    RobotContainer::intake->TakeInPowerCell();
    if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT && emptyPositionTriggered == false) {
      RobotContainer::intake->ConveyorSetSpeed(-.3);
    }

  }
  //tag to keep the conveyor from oscillating at five
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT) {
    fiveReached = true;
  }

  //makes it so the counter will only be reset if the ball is no longer in 5
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
    conveyorBackwardsCounter = 0;
  }

  // if (RobotContainer::intake->GetPowerCellCount >= 5) {
  //   RobotContainer::oi->SetControllerRumble(OI::driverController.get(), 1, true);
  //   RobotContainer::intake->Stop();
  //   RobotContainer::intake->StopConveyor();
  // }  



  // sees if one has been triggered
  if (RobotContainer::intake->GetInventory(1) == Intake::StorageState::PRESENT) {
    oneTriggered = true;
  }

   //sees if the emptyPosition has been triggered
  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT && oneTriggered == true) {
    emptyPositionTriggered = true;
  }

  if (emptyPositionTriggered == true && RobotContainer::intake->GetInventory(1) == Intake::StorageState::EMPTY) {
    badIntake = true;
    RobotContainer::intake->ConveyorSetSpeed(conveyorBackwardSpeed);
  }


}

// Called once the command ends or is interrupted.
void IntakePowerCell::End(bool interrupted) {
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
