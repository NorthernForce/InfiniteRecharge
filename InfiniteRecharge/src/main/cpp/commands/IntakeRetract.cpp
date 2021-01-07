/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeRetract.h"

IntakeRetract::IntakeRetract() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakeRetract::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeRetract::Execute() {
  RobotContainer::intake->IntakeIn();
}

// Called once the command ends or is interrupted.
void IntakeRetract::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakeRetract::IsFinished() { 
  //need to add a way to end?
  return false; 
}
