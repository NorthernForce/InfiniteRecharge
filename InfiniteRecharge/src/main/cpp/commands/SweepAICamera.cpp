/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SweepAICamera.h"
#include "commands/TurnToAngle.h"
#include <iostream>

SweepAICamera::SweepAICamera() {
  AddRequirements(RobotContainer::cameraMount.get());
  AddRequirements(RobotContainer::aiVisionTargetting.get());
  turnToAngle.reset(new TurnToAngle());
}

// Called when the command is initially scheduled.
void SweepAICamera::Initialize() {
  RobotContainer::cameraMount->Tilt(0);
}

// Called repeatedly when this Command is scheduled to run
void SweepAICamera::Execute() {
  AIVisionTargetting::Target powercell = AIVisionTargetting::Target::Powercell;
  if(!RobotContainer::aiVisionTargetting->CheckForTarget(powercell))
    RobotContainer::cameraMount->SweepForPowercells();
  else
    TurnToServoAngle();
}

void SweepAICamera::TurnToServoAngle() {
  int aiPanAng = RobotContainer::cameraMount->GetCurrentPan();
  int robotAng = RobotContainer::imu->GetRotation();
  char aiPanDir = RobotContainer::cameraMount->GetPanDirection();

    if (aiPanDir == 'l')
      turnToAngle->TurnInLoop(robotAng-aiPanAng);
    else if (aiPanDir == 'r')
      turnToAngle->TurnInLoop(robotAng+aiPanAng);
}

// Called once the command ends or is interrupted.
void SweepAICamera::End(bool interrupted) {}

// Returns true when the command should end.
bool SweepAICamera::IsFinished() { return true; }
