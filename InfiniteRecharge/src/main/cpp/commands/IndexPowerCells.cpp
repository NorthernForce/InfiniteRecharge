/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//NOTE: THIS IS NOT THE COMMAND WE ARE USING FOR INDEXING, it was just for testing separate parts - could delete now

#include "commands/IndexPowerCells.h"

IndexPowerCells::IndexPowerCells() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IndexPowerCells::Initialize() {
  emptyPosition = RobotContainer::intake->GetFirstEmptyPosition();
}


// Called repeatedly when this Command is scheduled to run
void IndexPowerCells::Execute() {
  //runs conveyor if there is a power cell in intake
  if (RobotContainer::intake->GetInventory(0) == Intake::StorageState::PRESENT) {
    RobotContainer::intake->RunConveyor();
    //std::cout << "running conveyor\n";
  } 
  //stops conveyor and rumbles if there are already three power cells // changed from 5
  else if (RobotContainer::intake->GetPowerCellCount() >= 3) {
    RobotContainer::oi->SetControllerRumble(OI::manipulatorController.get(), 1, true);
    RobotContainer::intake->Stop();
    RobotContainer::intake->StopConveyor();
  } 
}

// Called once the command ends or is interrupted.
void IndexPowerCells::End(bool interrupted) {
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool IndexPowerCells::IsFinished() { 
  if (RobotContainer::intake->GetInventory(emptyPosition) == Intake::StorageState::PRESENT)
    return true;
  else
    return false; 
}