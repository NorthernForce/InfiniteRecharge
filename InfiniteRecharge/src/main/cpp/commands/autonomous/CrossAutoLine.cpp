/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/CrossAutoLine.h"
#include "RobotContainer.h"

CrossAutoLine::CrossAutoLine() {
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());
}

// Called when the command is initially scheduled.
void CrossAutoLine::Initialize() {
  RobotContainer::drivetrain->DriveInInches(12, 0.5, 0.5);
}

// Called repeatedly when this Command is scheduled to run
void CrossAutoLine::Execute() {}

// Called once the command ends or is interrupted.
void CrossAutoLine::End(bool interrupted) {}

// Returns true when the command should end.
bool CrossAutoLine::IsFinished() { return false; }
