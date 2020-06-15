/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Servo.h>
#include <functional>

class CameraMount : public frc2::SubsystemBase {
 public:
  CameraMount();
  void Init();
  void Periodic();
  void SyncServoAngles();
  int GetServoAngleToTarget();
  void Sweep();
  void SetToZero();
  int GetCurrentPan();
  int GetPreviousPan();
  void Pan(int degrees);
  int GetCurrentTilt();
  int GetPreviousTilt();
  void Tilt(int degrees);
  char GetPanDirection();
  void RecoverOutOfRangeServo();

 private:
  int currentPan;
  int currentTilt;
  int previousPan;
  int previousTilt;
  char panDirection;
  char tiltDirection;
  int servoAngleToTarget;
  static int sweepPassCount;

  std::shared_ptr<frc::Servo> panServo;
  std::shared_ptr<frc::Servo> tiltServo;
};
