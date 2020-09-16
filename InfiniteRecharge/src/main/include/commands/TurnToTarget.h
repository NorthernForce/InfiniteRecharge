/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "commands/TurnToAngle.h"
#include "RobotContainer.h"

class TurnToTarget
    : public frc2::CommandHelper<frc2::CommandBase, TurnToTarget> {
 public:
  TurnToTarget();
  void Initialize() override;
  void EnableTurningMode();
  void DisableTurningMode();
  bool IsTurnOnButtonEnabled();
  bool IsAutoTurningEnabled();
  void Execute() override;
  void TurnRobotToTarget();
  void TurnToAng(int ang);
  int GetDistanceToTargetBeforeTurn();
  bool HasRobotTurned();
  bool IsTurningScheduled();
  void End(bool interrupted) override;
  bool IsFinished() override;
  void Reset();

 private:
  std::shared_ptr<TurnToAngle> turnToAngle;
  AIVisionTargetting::Target powercell = AIVisionTargetting::Target::Powercell;
  static bool turningMode;
  static bool hasTurned;
  bool hasStartedTurn = false;
  static int distanceToTargetBeforeTurn;
};
