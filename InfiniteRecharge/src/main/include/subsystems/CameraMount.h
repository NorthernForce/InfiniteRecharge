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
  void Pan(int degrees);
  int GetCurrentPan();
  int GetPreviousPan();
  void Tilt(int degrees);
  int GetCurrentTilt();
  int GetPreviousTilt();
  void SetToZero();
  void SetAngles(int panAngle, int tiltAngle);
  static bool IntervaledExecution(std::function<void()> periodicFunction, unsigned msInterval);
  static void SweepForPowercells();
  int GetServoAngleToTarget();

  void Periodic();

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
