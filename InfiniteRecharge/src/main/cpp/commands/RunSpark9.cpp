/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunSpark9.h"
#include "RobotContainer.h"

RunSpark9::RunSpark9(double speed) {
  AddRequirements(RobotContainer::intake.get());
  m_speed = speed;
}

// Called when the command is initially scheduled.
void RunSpark9::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunSpark9::Execute() {
  RobotContainer::intake->SetArm(m_speed);
  std::cout << "running arm\n";
}

// Called once the command ends or is interrupted.
void RunSpark9::End(bool interrupted) {
  RobotContainer::intake->SetArm(0);
}

// Returns true when the command should end.
bool RunSpark9::IsFinished() { return false; }
