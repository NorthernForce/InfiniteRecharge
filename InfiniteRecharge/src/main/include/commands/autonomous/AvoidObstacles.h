// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "RobotContainer.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AvoidObstacles
    : public frc2::CommandHelper<frc2::CommandBase, AvoidObstacles> {
 public:
  AvoidObstacles();

  void Initialize() override;

  bool TestForCollision(double xTarget, double yTarget);

  auto NearestGameCoordinate();

  void UpdatePosition();

  double NGCAngle();

  double NGCDistance();

  bool WillHitNGC();

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  double xCurrent;
  double yCurrent;
  std::pair<double, double> ngc;
};
