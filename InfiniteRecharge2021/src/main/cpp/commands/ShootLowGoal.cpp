/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootLowGoal.h"
#include "RobotContainer.h"

ShootLowGoal::ShootLowGoal() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::shooter.get());
}

// Called when the command is initially scheduled.
void ShootLowGoal::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShootLowGoal::Execute() {
  RobotContainer::shooter->Shoot();
    //changed from 5 to 4
    if (RobotContainer::intake->GetInventory(4) == Intake::StorageState::EMPTY) {
      RobotContainer::intake->RunConveyor();
    }
    else {
      RobotContainer::intake->StopConveyor();
    }

    //std::cout << "RPM: " << RobotContainer::shooter->GetTargetRPM() << "\n";
    double error = RobotContainer::shooter->GetError();
    if (abs(error) < 100) { // try and tie that into the setpoint of the PID, there may be an acceptable range you want to use instead of a rigid number
      RobotContainer::intake->ConveyorSetSpeed(-0.65);
    }
    else {
      RobotContainer::intake->StopConveyor();
    }
}

// Called once the command ends or is interrupted.
void ShootLowGoal::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootLowGoal::IsFinished() { return false; }
