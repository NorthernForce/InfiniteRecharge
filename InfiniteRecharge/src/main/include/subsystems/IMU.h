/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <AHRS.h>

class IMU : public frc2::SubsystemBase {
 public:
  IMU();
  void Init();
  void Periodic();
  double GetRollAngle();
  double GetRotation();
  void Reset();

 private:
  std::shared_ptr<AHRS> ahrs;
  double previousAccelX;
  double previousAccelY;
};
