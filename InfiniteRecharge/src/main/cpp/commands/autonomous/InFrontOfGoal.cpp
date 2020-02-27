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
#include <functional>

InFrontOfGoal::InFrontOfGoal() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());
  turnToAngle.reset(new TurnToAngle());
  
}

// Called when the command is initially scheduled.
void InFrontOfGoal::Initialize() {
  RobotContainer::shooter->Shoot();
}

// Called repeatedly when this Command is scheduled to run
void InFrontOfGoal::Execute() {
  RunOnce(turnToAngle->TurnInLoop(90));
  RobotContainer::drivetrain->AutoDrive(60, 0.5, 0.5);
  RunOnce(turnToAngle->TurnInLoop(90));
  RunOnce(RobotContainer::intake->SetArmDown());
  RobotContainer::drivetrain->AutoDrive(144, 0.5, 0.5);
  RunOnce(RobotContainer::intake->SetArmUp();
}

// Called once the command ends or is interrupted.
void InFrontOfGoal::End(bool interrupted) {}

// Returns true when the command should end.
bool InFrontOfGoal::IsFinished() { return false; }

void InFrontOfGoal::RunOnce(std::function<void()> function()) {
  int counter;
  if (counter < 1) 
    function();
  counter++;
}