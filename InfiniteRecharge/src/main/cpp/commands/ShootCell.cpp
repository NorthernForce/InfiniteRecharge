/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootCell.h"
#include <frc/DriverStation.h>
#include "RobotContainer.h"
#include <iostream>

ShootCell::ShootCell(double rtTriggerAxis ) {
  // Use addRequirements() here to declare subsystem dependencies.
  m_rtTriggerAxis = rtTriggerAxis;
  AddRequirements(RobotContainer::shooter.get());
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ShootCell::Initialize() {
  double ramp = RobotContainer::oi->GetShooterRampRate(); //TODO: fix these
//  RobotContainer::shooter->ConfigureSpark(ramp);
}

// Called repeatedly when this Command is scheduled to run
void ShootCell::Execute() {
  if (m_rtTriggerAxis > 0.5) {
    RobotContainer::shooter->Shoot();
    if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
      RobotContainer::intake->RunConveyor();
    }
    std::cout << "RPM: " << RobotContainer::shooter->GetRPM() << "\n";
    if (RobotContainer::shooter->GetRPM() >= 3500) {
      RobotContainer::intake->RunConveyor();
    }
    else {
      RobotContainer::intake->StopConveyor();
    }
  }
}

// Called once the command ends or is interrupted.
void ShootCell::End(bool interrupted) {
  RobotContainer::shooter->SetSpeed(0);
  RobotContainer::intake->StopConveyor();
}

// Returns true when the command should end.
bool ShootCell::IsFinished() { return false; }
