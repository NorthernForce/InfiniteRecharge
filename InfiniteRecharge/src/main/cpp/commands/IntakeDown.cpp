/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeDown.h"
#include "RobotContainer.h"

IntakeDown::IntakeDown() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void IntakeDown::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeDown::Execute() {
  RobotContainer::intake->SetArm(-0.7);
}

// Called once the command ends or is interrupted.
void IntakeDown::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakeDown::IsFinished() { return false; }
