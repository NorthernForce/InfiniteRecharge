/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/InFrontOfGoal.h"
#include "RobotContainer.h"


InFrontOfGoal::InFrontOfGoal() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void InFrontOfGoal::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void InFrontOfGoal::Execute() {
  RobotContainer::drivetrain->DriveInInches(0.5, 0.5, 60);
  RobotContainer::drivetrain->DriveInInches(0.5, 0.5, 144);
}

// Called once the command ends or is interrupted.
void InFrontOfGoal::End(bool interrupted) {}

// Returns true when the command should end.
bool InFrontOfGoal::IsFinished() { return false; }
