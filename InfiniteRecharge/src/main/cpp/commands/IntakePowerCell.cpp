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
//   AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakePowerCell::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakePowerCell::Execute() {

finished = RobotContainer::intake->NewTrevinIntake();

}

// Called once the command ends or is interrupted.
void IntakePowerCell::End(bool interrupted) {
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool IntakePowerCell::IsFinished() { return finished; }
