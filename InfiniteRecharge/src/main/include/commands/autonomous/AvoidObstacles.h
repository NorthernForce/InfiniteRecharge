// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"
#include "MoveToCoordinate.h"

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
  AvoidObstacles(CPlane::Point end, std::vector<CPlane::Point> obstacles={}, double speed=0.3);

  void Initialize() override;

  bool TestForCollision(double xTarget, double yTarget);

  auto NearestObstacle();

  void UpdatePosition();

  double NGCAngle();

  double NGCDistance();

  bool WillHitNGC();

  bool NGCisObstacle();

  double CorrectionAmount();

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  std::unique_ptr<MoveToCoordinate> moveToCoordinate;
  std::vector<CPlane::Point> obstacleList;
  CPlane::Point robot;
  int obstacleListIndex;
  CPlane::Point obstacle;
  double obstacleDistance;
  CPlane::Point newObstacle;
  double horizontalDistance;
};
