/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootCell.h"
#include <frc/DriverStation.h>
#include <RobotContainer.h>

ShootCell::ShootCell(double rtTriggerAxis) {
  // Use addRequirements() here to declare subsystem dependencies.
  m_rtTriggerAxis = rtTriggerAxis;
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void ShootCell::Initialize(){}

// Called repeatedly when this Command is scheduled to run
void ShootCell::Execute() {
  if(m_rtTriggerAxis > .5) {
  RobotContainer::shooter->ShootCell();
  }
}


// Called once the command ends or is interrupted.
void ShootCell::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootCell::IsFinished() { return false; }
