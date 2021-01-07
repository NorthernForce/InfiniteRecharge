/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeExtend.h"

IntakeExtend::IntakeExtend() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakeExtend::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeExtend::Execute() {
  RobotContainer::intake->IntakeOut();
}

// Called once the command ends or is interrupted.
void IntakeExtend::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakeExtend::IsFinished() { 
  //need to add a way to end?
  return false; 
}
