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

void ShootCell::Initialize() {}

void ShootCell::Execute() {
  double rtTriggerAxis = RobotContainer::oi->driverController->GetRawAxis(OI::XboxAxis::rt_trigger);
  if (rtTriggerAxis > 0.5) {
    // outputs for tuning  
    std::cout << "error: " << RobotContainer::shooter->GetError() << '\n';
    std::cout << "targetRPM: " << RobotContainer::shooter->GetTargetRPM() << '\n';
    std::cout << "currentRPM: " << RobotContainer::shooter->GetCurrentRPM() << '\n';
    RobotContainer::shooter->Shoot();
    if (RobotContainer::shooter->GetError() < 100) {
      RobotContainer::intake->ConveyorSetSpeed(conveyorShooterSpeed);
    }
    else {
      //changed from 5 to 4
      if (RobotContainer::intake->GetInventory(4) == Intake::StorageState::EMPTY)
        RobotContainer::intake->RunConveyor();
      else {
        conveyorBackwardsCounter++;
        if (conveyorBackwardsCounter >= 10) {
          RobotContainer::intake->StopConveyor();
          conveyorBackwardsCounter = 0;
        }
      }
    }
  }
}
void ShootCell::End(bool interrupted) {
  RobotContainer::shooter->SetCurrentRPMTo(0); // consider adding an idle state where the rpm is lower than the target but not off
  RobotContainer::intake->StopConveyor(); 
}

bool ShootCell::IsFinished() { return false; }
