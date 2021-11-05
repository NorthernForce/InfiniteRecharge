/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootCell.h"
#include <frc/DriverStation.h>
#include "OI.h"
#include <iostream>

ShootCell::ShootCell() {
  // AddRequirements(RobotContainer::shooter.get());
  // AddRequirements(RobotContainer::intake.get());
}

void ShootCell::Initialize() {}

void ShootCell::Execute() {
    RobotContainer::shooter->Shoot();
    if (abs(RobotContainer::shooter->GetError()) < 100) {
        RobotContainer::intake->ConveyorSetSpeed(conveyorShooterSpeed);
    }
    else {
        if (RobotContainer::intake->GetInventory(4) == Intake::StorageState::EMPTY)
            RobotContainer::intake->RunConveyor();
        else
            RobotContainer::intake->StopConveyor();
    }
}

void ShootCell::End(bool interrupted) {
  RobotContainer::shooter->SetRawSpeed(0);
  RobotContainer::intake->StopConveyor(); 
}

bool ShootCell::IsFinished() { return false; }