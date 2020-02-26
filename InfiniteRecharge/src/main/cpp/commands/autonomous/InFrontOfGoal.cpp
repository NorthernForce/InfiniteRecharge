/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/InFrontOfGoal.h"
#include "RobotContainer.h"
#include "commands/TurnToAngle.h"
#include "commands/ShootCell.h"


InFrontOfGoal::InFrontOfGoal() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());
  turnToAngle.reset(new TurnToAngle());
  
}

// Called when the command is initially scheduled.
void InFrontOfGoal::Initialize() {
  RobotContainer::shooter->Shoot();
  turnToAngle->TurnInLoop(90);
  RobotContainer::drivetrain->DriveInInches(60, 0.5, 0.5);
  turnToAngle->TurnInLoop(90);
  //// TODO: Intake stuff goes here
  RobotContainer::drivetrain->DriveInInches(144, 0.5, 0.5);

}

// Called repeatedly when this Command is scheduled to run
void InFrontOfGoal::Execute() {}

// Called once the command ends or is interrupted.
void InFrontOfGoal::End(bool interrupted) {}

// Returns true when the command should end.
bool InFrontOfGoal::IsFinished() { return false; }
