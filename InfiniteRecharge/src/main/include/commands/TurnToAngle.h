/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TurnToAngle
    : public frc2::CommandHelper<frc2::CommandBase, TurnToAngle> {
 public:
  TurnToAngle(double targetAngle = 0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  double targetAngle = 0;
  double totalTargetAngle = 0;

  const double pValue = 1.3;
  const double iValue = 0;
  const double dValue = 0.5;

  const double maxTurnSpeed = 0.35;
  const double minError = 0.05;

  double error = 0;
  double errorPrior = 0;
  double integral = 0;
  double derivative = 0;

  int defaultPeriodInMs = 20;
};
