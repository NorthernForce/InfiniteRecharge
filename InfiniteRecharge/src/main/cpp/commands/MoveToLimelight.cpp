/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveToLimelight.h"
#include "commands/TurnToAngle.h"

MoveToLimelight::MoveToLimelight() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::limelight.get());
  turnToAngle.reset(new TurnToAngle());
}

// Called when the command is initially scheduled.
void MoveToLimelight::Initialize() {
  RobotContainer::limelight->PutNumberToTable("ledMode", 3);
  std::cout << "initialize" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void MoveToLimelight::Execute() {
  std::cout << "execute1" << std::endl;
  limeLightOffset = RobotContainer::limelight->GetXOffset();
  std::cout << "execute2" << std::endl;
  isTargetThere = RobotContainer::limelight->IsTargetThere();
  std::cout << "execute3" << std::endl;
  turnToAngle->TurnInLoop(limeLightOffset);
}

// Called once the command ends or is interrupted.
void MoveToLimelight::End(bool interrupted) {
  RobotContainer::limelight->PutNumberToTable("ledMode", 1);
  RobotContainer::drivetrain->Drive(0,0);
  std::cout << "end" << std::endl;
}

// Returns true when the command should end.
bool MoveToLimelight::IsFinished() { return false; }
