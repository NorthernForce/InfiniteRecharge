/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootByDist.h"
#include "RobotContainer.h"

ShootByDist::ShootByDist() {
  AddRequirements(RobotContainer::shooter.get());
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ShootByDist::Initialize() {
  // double d = RobotContainer::ultrasonic->GetDistance();
  // double speed = sqrt(-1*(d*d*-368.09)/(0.719185573395*(d-73.5)));
  // rpm = (60*speed)/37.6991118431;
}

void ShootByDist::Execute() {
      RobotContainer::shooter->Shoot();
      if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
        RobotContainer::intake->RunConveyor();
      }
      else {
        if (RobotContainer::shooter->GetTargetRPM() >= 3600) // try and tie that into the setpoint of the PID, there may be an acceptable range you want to use instead of a rigid number
          RobotContainer::intake->RunConveyor();
        else 
          RobotContainer::intake->StopConveyor();
      }
      // std::cout << "RPM: " << RobotContainer::shooter->GetRPM() << "\n";
    }


void ShootByDist::End(bool interrupted) {
  RobotContainer::shooter->SetRawSpeed(0);
  RobotContainer::intake->StopConveyor(); 
}

// Returns true when the command should end.
bool ShootByDist::IsFinished() { return false; }
