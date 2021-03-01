/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Timer.h>
#include <AHRS.h>

class IMU : public frc2::SubsystemBase {
 public:
  IMU();
  void Init();
  void Periodic();
  double GetRollAngle();
  double GetRotation();
  void ZeroRotation();
  void Reset();
  double GetAcceleration();
  bool IsMoreTorqueNeeded();

 private:
  std::shared_ptr<AHRS> ahrs;
  std::shared_ptr<frc::Timer> accelerationRateTimer;
  double currentAccelX;
  double currentAccelY;
  double previousAccelX;
  double previousAccelY;
  double torqueThreshold;
};
