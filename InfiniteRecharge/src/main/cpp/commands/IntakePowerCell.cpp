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
  zeroHasBeenTriggered = false;
}

//***************************************************************************
////TODO: NEED to check if Pos. 5 is empty before starting Intake!!
//****************************************************************************
// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {
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
    //run conveyor and intake to take in power cell
    RobotContainer::intake->TakeInPowerCell();
    if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT) {
      RobotContainer::intake->ConveyorSetSpeed(conveyorRunSpeed);
      zeroHasBeenTriggered = true;
    }
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

  ////TODO: Consider adding a check to make sure this isn't the first power cell to make sure cell will actually reach 0
  ////TODO: find out if when the cell exits 0 is 1 triggered? (how close together are the positions?)

  //checks to make sure that the power cell was intaked properly and runs conveyor backward if not
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::EMPTY && zeroHasBeenTriggered == true && RobotContainer::intake->GetInventory(1) == Intake::StorageState::EMPTY) {
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
  //makes sure ball has cleared 0 and there isnt a gap before stopping
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::EMPTY && zeroHasBeenTriggered == true && RobotContainer::intake->GetInventory(1) == Intake::StorageState::PRESENT)
    return true;
  else
    return false; 
}
