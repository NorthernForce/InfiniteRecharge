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
  if(RobotContainer::aiVisionTargetting->CheckForTarget(powercell))
    TurnToServoAngle();
  else
    RobotContainer::cameraMount->SweepForPowercells();
}

void SweepAICamera::TurnToServoAngle() {
  int servoPanAng = RobotContainer::cameraMount->GetCurrentPan();
  char servoPanDir = RobotContainer::cameraMount->GetPanDirection();
  std::vector<double> pcOffsetInCamera = RobotContainer::aiComms->GetValueArray(RobotContainer::aiComms->powercellOffsetInCam);

  AdjustServoAngToPCOffset(servoPanAng, pcOffsetInCamera[0]);
  TurnRobotUsingServoAngle(servoPanAng, servoPanDir);
}

void SweepAICamera::AdjustServoAngToPCOffset(int servoAng, double pcOffset) {
  if (pcOffset < -10)
    RobotContainer::cameraMount->Pan(servoAng+=1);
  else if (pcOffset > 10)
    RobotContainer::cameraMount->Pan(servoAng-=1);
}

void SweepAICamera::TurnRobotUsingServoAngle(int servoAng, char servoDir) {
  int robotAng = RobotContainer::imu->GetRotation();
  if (servoDir == 'l')
    TurnToAngle(robotAng-servoAng);
  else if (servoDir == 'r')
    TurnToAngle(robotAng+servoAng);
}

// Called once the command ends or is interrupted.
void SweepAICamera::End(bool interrupted) {}

// Returns true when the command should end.
bool SweepAICamera::IsFinished() { return true; }
