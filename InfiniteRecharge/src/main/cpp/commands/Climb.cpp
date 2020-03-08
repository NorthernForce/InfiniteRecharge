/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Climb.h"

Climb::Climb(std::function<double()> speed) : m_speed(speed) {
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void Climb::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {
  if (abs(m_speed()) > 0.3) {
    RobotContainer::climber->SetLifter(abs(m_speed()) / 2);
  }
  else {
    RobotContainer::climber->SetLifter(0.0);
  }
}

// Called once the command ends or is interrupted.
void Climb::End(bool interrupted) {
  RobotContainer::climber->SetLifter(0);
}

// Returns true when the command should end.
bool Climb::IsFinished() { return false; }
