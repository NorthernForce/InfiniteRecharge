/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/InventoryPowerCells.h"

InventoryPowerCells::InventoryPowerCells() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void InventoryPowerCells::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void InventoryPowerCells::Execute() {
  RobotContainer::intake->InventoryPowerCells();
}

// Called once the command ends or is interrupted.
void InventoryPowerCells::End(bool interrupted) {}

// Returns true when the command should end.
bool InventoryPowerCells::IsFinished() { return false; }
