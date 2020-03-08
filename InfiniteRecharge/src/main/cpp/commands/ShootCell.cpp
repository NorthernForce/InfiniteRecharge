/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootCell.h"
#include <frc/DriverStation.h>
#include "OI.h"
#include "RobotContainer.h"
#include <iostream>

ShootCell::ShootCell() {
  // AddRequirements(RobotContainer::shooter.get());
  // AddRequirements(RobotContainer::intake.get());
}

void ShootCell::Initialize() {
  double ramp = RobotContainer::oi->GetShooterRampRate();
  RobotContainer::shooter->ConfigureSpark(ramp);
}

void ShootCell::Execute() {
  double rtTriggerAxis = RobotContainer::oi->driverController->GetRawAxis(OI::XboxAxis::rt_trigger);
  if (rtTriggerAxis > 0.5) {
    RobotContainer::shooter->Shoot();
    if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
      RobotContainer::intake->RunConveyor();
    }
    else {
      RobotContainer::intake->StopConveyor();
    }

    //std::cout << "RPM: " << RobotContainer::shooter->GetRPM() << "\n";
    if (RobotContainer::shooter->GetRPM() > 2000)
      RobotContainer::intake->ConveyorSetSpeed(-0.65);
    else
      RobotContainer::intake->StopConveyor();
  }
}

void ShootCell::End(bool interrupted) {
  RobotContainer::shooter->SetSpeed(0); // consider adding an idle state where the rpm is lower than the target but not off, also is this set to coast?
  RobotContainer::intake->StopConveyor(); 
}

bool ShootCell::IsFinished() { return false; }
