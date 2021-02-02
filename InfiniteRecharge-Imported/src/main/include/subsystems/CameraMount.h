/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Servo.h>
#include "subsystems/AIVisionTargetting.h"
#include <deque>

class CameraMount : public frc2::SubsystemBase {
 public:
  CameraMount();
  void Init();
  void Periodic();
  int GetServoAngleToTarget();
  void SmartSweep();
  void Sweep();
  void PauseSweep();
  void ResumeSweep();
  bool GetIsSweeping();
  void CenterTarget();
  void MoveServoBackToTarget();
  void SetToZero();
  int GetCurrentPan();
  int GetPreviousPan();
  int GetAvgOfRecentPans();
  void Pan(int degrees);
  int GetCurrentTilt();
  int GetPreviousTilt();
  void Tilt(int degrees);
  char GetPanDirection();

 private:
  void RecoverOutOfRangeServo();
  void SetLastNonZeroPcOffset();
  void LimitStoredAngles();

  int currentPan;
  int currentTilt;
  int previousPan;
  std::deque<int> recentPanAngles;
  int previousTilt;
  char panDirection;
  char tiltDirection;
  int servoAngleToTarget;
  static int sweepPassCount;
  int offsetCorrectLimiter;
  double pcOffset;
  double lastNonZeroPcOffset;
  bool hasMovedServoBackToTarget = false;
  int cycleCounter;
  int recentSweepStops;
  int cycleThresh = 3;
  bool overrideSweep;

  std::shared_ptr<frc::Servo> panServo;
  std::shared_ptr<frc::Servo> tiltServo;
};
