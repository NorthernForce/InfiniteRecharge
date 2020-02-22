/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveToColor.h"
#include "RobotContainer.h"

MoveToColor::MoveToColor() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::wackyWheel.get());
}

// Called when the command is initially scheduled.
void MoveToColor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveToColor::Execute() {}








// Called once the command ends or is interrupted.
void MoveToColor::End(bool interrupted) {}

// Returns true when the command should end.
bool MoveToColor::IsFinished() { return false; }
