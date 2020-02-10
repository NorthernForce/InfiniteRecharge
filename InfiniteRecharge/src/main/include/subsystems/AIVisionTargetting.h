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

  bool CheckForTarget();
  Target CheckTargetType();
  int GetAngleOfTarget();
  double GetTargetOffsetInCamera();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:

};

enum class Target {
  Powercell,
  UpperGoal,
  LowerGoal
};