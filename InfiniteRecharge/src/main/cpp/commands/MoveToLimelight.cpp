/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveToLimelight.h"
#include "commands/TurnToAngle.h"
#include <frc2/command/Command.h>
#include <iostream>

MoveToLimelight::MoveToLimelight() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::limelight.get());
}

// Called when the command is initially scheduled.
void MoveToLimelight::Initialize() {
  RobotContainer::limelight->PutNumberToTable("ledMode", 3);
}

// Called repeatedly when this Command is scheduled to run
void MoveToLimelight::Execute() {
  limeLightOffset = RobotContainer::limelight->GetXOffset();
  isTargetThere = RobotContainer::limelight->IsTargetThere();
  std::cout << "is target there: " << isTargetThere << std::endl;
  std::cout << "limelight offset: " << limeLightOffset << std::endl;
  if (isTargetThere == true) {
    RobotContainer::drivetrain->SimpleTurnToAngle(limeLightOffset);
    frc2::Command* turnToLimelight = new TurnToAngle(limeLightOffset);
    //if (!turnToLimelight->IsScheduled())
    //  turnToLimelight->Schedule();
  }
}

// Called once the command ends or is interrupted.
void MoveToLimelight::End(bool interrupted) {
  RobotContainer::limelight->PutNumberToTable("ledMode", 1);
  RobotContainer::drivetrain->Drive(0,0);
}

// Returns true when the command should end.
bool MoveToLimelight::IsFinished() { return false; }
