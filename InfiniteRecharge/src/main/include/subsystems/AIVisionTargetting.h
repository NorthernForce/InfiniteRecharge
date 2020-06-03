/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class AIVisionTargetting : public frc2::SubsystemBase {
 public:
  AIVisionTargetting();
  enum class Target {
    Powercell,
    Goal,
    None
  };
  bool CheckForTarget(Target type);
  Target CheckTargetType();
  void RefreshTargetPositioning();
  double RoboAngleToTarget();
  double RoboDistToTarget();
  void Periodic();

 private:
  bool targetFound;
  double targetPositionX;
  double targetPositionY;
  AIVisionTargetting::Target powercell = AIVisionTargetting::Target::Powercell;
};
