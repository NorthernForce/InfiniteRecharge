/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunIntakeMotor.h"
#include <iostream>

RunIntakeMotor::RunIntakeMotor(double speed) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
  m_speed = speed;
}

// Called when the command is initially scheduled.
void RunIntakeMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntakeMotor::Execute() {
  if (m_speed > 0.3)
    std::cout << "in execute\n";
    RobotContainer::intake->TakeInPowerCell();
}

// Called once the command ends or is interrupted.
void RunIntakeMotor::End(bool interrupted) {
  RobotContainer::intake->Stop();
}

// Returns true when the command should end.
bool RunIntakeMotor::IsFinished() { return false; }
