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
void IndexPowerCells::Initialize() {}


// Called repeatedly when this Command is scheduled to run
void IndexPowerCells::Execute() {

  intakeDone = RobotContainer::intake->NewTrevinIntake();

}

// Called once the command ends or is interrupted.
void IndexPowerCells::End(bool interrupted) {
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool IndexPowerCells::IsFinished() { return intakeDone; }