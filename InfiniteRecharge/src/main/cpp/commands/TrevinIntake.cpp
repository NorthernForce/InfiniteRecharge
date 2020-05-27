/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TrevinIntake.h"

TrevinIntake::TrevinIntake() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void TrevinIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TrevinIntake::Execute() {
  isFinished = RobotContainer::intake->NewTrevinIntake();
  std::cout << "Intake Running\n";
}

// Called once the command ends or is interrupted.
void TrevinIntake::End(bool interrupted)  {
  RobotContainer::intake->Stop();
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool TrevinIntake::IsFinished() {
    return isFinished;
}