/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootCellWithoutTrigger.h"
#include <frc/DriverStation.h>
#include "OI.h"
#include "RobotContainer.h"
#include <iostream>

ShootCellWithoutTrigger::ShootCellWithoutTrigger() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::shooter.get());
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ShootCellWithoutTrigger::Initialize() {
  double ramp = RobotContainer::oi->GetShooterRampRate();
  RobotContainer::shooter->ConfigureSpark(ramp);
}

// Called repeatedly when this Command is scheduled to run
void ShootCellWithoutTrigger::Execute() {
  RobotContainer::shooter->Shoot();
    if (RobotContainer::intake->GetInventory(5) == Intake::StorageState::EMPTY) {
      RobotContainer::intake->RunConveyor();
    }
    else {
      RobotContainer::intake->StopConveyor();
    }

    //std::cout << "RPM: " << RobotContainer::shooter->GetRPM() << "\n";
    double error = RobotContainer::shooter->GetError();
    if (abs(error) < 100) { // try and tie that into the setpoint of the PID, there may be an acceptable range you want to use instead of a rigid number
      RobotContainer::intake->ConveyorSetSpeed(-0.65);
    }
    else {
      RobotContainer::intake->StopConveyor();
    }
  }
}

// Called once the command ends or is interrupted.
void ShootCellWithoutTrigger::End(bool interrupted) {
  RobotContainer::shooter->SetSpeed(0); // consider adding an idle state where the rpm is lower than the target but not off, also is this set to coast?
  RobotContainer::intake->StopConveyor(); 
}

// Returns true when the command should end.
bool ShootCellWithoutTrigger::IsFinished() { return false; }
