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
  AddRequirements(RobotContainer::shooter.get());
  AddRequirements(RobotContainer::intake.get());
}

void ShootCell::Initialize() {
  double ramp = RobotContainer::oi->GetShooterRampRate();
  RobotContainer::shooter->ConfigureSpark(ramp);
}

void ShootCell::Execute() {
  std::cout << "error: " << RobotContainer::shooter->GetError() << '\n';
  std::cout << "targetRPM: " << RobotContainer::shooter->GetTargetRPM() << '\n';
  std::cout << "currentRPM: " << RobotContainer::shooter->GetCurrentRPM() << '\n';

  RobotContainer::shooter->Shoot();
  if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
    RobotContainer::intake->RunConveyor();
  }
  else {
    if (RobotContainer::shooter->GetError() < 100)
      RobotContainer::intake->RunConveyorToShoot();
    else
      RobotContainer::intake->StopConveyor();
  }
}  
void ShootCell::End(bool interrupted) {
  RobotContainer::shooter->SetSpeed(0); // consider adding an idle state where the rpm is lower than the target but not off
  RobotContainer::intake->StopConveyor(); 
}

bool ShootCell::IsFinished() { return false; }
