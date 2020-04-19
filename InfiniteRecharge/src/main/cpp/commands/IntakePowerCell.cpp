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
 // zeroHasBeenTriggered = false;
}

//***************************************************************************
////TODO: NEED to check if Pos. 5 is empty before starting Intake!!
//****************************************************************************
// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {
  
  std::cout << "Empty Position is " << emptyPosition <<  "\n";

  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT) {
    std::cout << "Empty Position " << emptyPosition <<  " full\n";
  }
  else {
    std::cout << "Empty Position " << emptyPosition <<  " empty\n";
  }

  //stops conveyor when power cell has cleared pos 0
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT && conveyorBackwardsCounter <= 10) {

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

  else {
    ////TODO: if we are basing the conveyor stopping on the empty position, should we just take out the 0 pos code?
    //run conveyor and intake to take in power cell
    RobotContainer::intake->TakeInPowerCell();
    if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT && RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::EMPTY) {
      RobotContainer::intake->ConveyorSetSpeed(conveyorRunSpeed);
    }
    
    //  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT) {
    //   zeroHasBeenTriggered = true;
    // }
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

  //will run conveyor backward if power cell wasn't intaked properly
  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT && RobotContainer::intake->GetInventory(1) == Intake::StorageState::EMPTY) {
    RobotContainer::intake->ConveyorSetSpeed(conveyorBackwardSpeed);
  }

  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT) {
    emptyPositionTriggered = true;
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
