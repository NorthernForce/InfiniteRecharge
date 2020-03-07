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

class SweepAICamera
    : public frc2::CommandHelper<frc2::CommandBase, SweepAICamera> {
 public:
  SweepAICamera();
  void Initialize() override;
  void Execute() override;
  void TurnToServoAngle();
  void AdjustServoAngToPCOffset(int servoAng, double pcOffset);
  void TurnRobotUsingServoAngle(int servoAng, char servoDir);
  void End(bool interrupted) override;
  bool IsFinished() override;
 private:
  std::shared_ptr<TurnToAngle> turnToAngle;
};
