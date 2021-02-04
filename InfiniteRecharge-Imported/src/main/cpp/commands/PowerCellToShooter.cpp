/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//not sure if we will need this command 

#include "commands/PowerCellToShooter.h"

PowerCellToShooter::PowerCellToShooter() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void PowerCellToShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PowerCellToShooter::Execute() {
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
     RobotContainer::intake->RunConveyor();
  }
}

// Called once the command ends or is interrupted.
void PowerCellToShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool PowerCellToShooter::IsFinished() { 
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::PRESENT) {
    RobotContainer::intake->StopConveyor();
    return true;
  }
  else {
  return false; 
  }
}
