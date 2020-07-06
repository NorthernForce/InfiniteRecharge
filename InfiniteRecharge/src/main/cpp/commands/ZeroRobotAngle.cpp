/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ZeroRobotAngle.h"

ZeroRobotAngle::ZeroRobotAngle() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ZeroRobotAngle::Initialize() {
  RobotContainer::navigation->ZeroAngle();
}

// Called repeatedly when this Command is scheduled to run
void ZeroRobotAngle::Execute() {}

// Called once the command ends or is interrupted.
void ZeroRobotAngle::End(bool interrupted) {}

// Returns true when the command should end.
bool ZeroRobotAngle::IsFinished() { return true; }
