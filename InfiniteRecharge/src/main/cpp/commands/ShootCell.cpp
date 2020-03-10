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
  AddRequirements(RobotContainer::shooter.get());
  AddRequirements(RobotContainer::intake.get());
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
      RobotContainer::intake->RunConveyorToShoot();
    }
    else {
      if (RobotContainer::shooter->GetRPM() > 2200) { // try and tie that into the setpoint of the PID, there may be an acceptable range you want to use instead of a rigid number
        RobotContainer::intake->RunConveyorToShoot();
      }
      else {
        RobotContainer::intake->StopConveyor();
      }
    }
  }
}

void ShootCell::End(bool interrupted) {
  RobotContainer::shooter->SetSpeed(0); // consider adding an idle state where the rpm is lower than the target but not off, also is this set to coast?
  RobotContainer::intake->StopConveyor(); 
}

bool ShootCell::IsFinished() { return false; }
