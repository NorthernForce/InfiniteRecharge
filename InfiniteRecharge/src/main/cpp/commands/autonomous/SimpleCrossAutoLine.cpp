/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/SimpleCrossAutoLine.h"
#include "RobotContainer.h"

SimpleCrossAutoLine::SimpleCrossAutoLine() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void SimpleCrossAutoLine::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SimpleCrossAutoLine::Execute() {
  auto encoderRotations = RobotContainer::drivetrain->GetEncoderRotations();
  RobotContainer::drivetrain->DriveUsingSpeeds(0.2, 0.2);
  if (((encoderRotations.second)*Constants::Shifting::highMultiplier) > 35)
    RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
}

// Called once the command ends or is interrupted.
void SimpleCrossAutoLine::End(bool interrupted) {}

// Returns true when the command should end.
bool SimpleCrossAutoLine::IsFinished() { return false; }