/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SafeCamera.h"
#include "RobotContainer.h"

SafeCamera::SafeCamera() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::cameraMount.get());
}

// Called when the command is initially scheduled.
void SafeCamera::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SafeCamera::Execute() {
    RobotContainer::cameraMount->Pan(180);
    RobotContainer::cameraMount->Tilt(0);
}

// Called once the command ends or is interrupted.
void SafeCamera::End(bool interrupted) {}

// Returns true when the command should end.
bool SafeCamera::IsFinished() {
    return RobotContainer::cameraMount->GetCurrentPan() > 165;
}
