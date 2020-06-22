/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutoShootCell.h"
#include "RobotContainer.h"

AutoShootCell::AutoShootCell() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void AutoShootCell::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoShootCell::Execute() {
   if (RobotContainer::shooter->GetError() < 100) {
      RobotContainer::intake->ConveyorSetSpeed(-0.5);
    }
}

// Called once the command ends or is interrupted.
void AutoShootCell::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoShootCell::IsFinished() {
  if(RobotContainer::intake->IsConveyorEmpty() == true) {
    return true;
  } else {
    return false;
  }
}
