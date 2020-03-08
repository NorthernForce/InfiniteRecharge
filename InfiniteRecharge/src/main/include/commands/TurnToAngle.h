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
  TurnToAngle(double target=targetAngle);
  void Initialize() override;
  void Execute() override;
  void TurnInLoop(double target=targetAngle);
  void End(bool interrupted) override;
  bool CheckIfFinished();
  bool IsFinished() override;

 private:
  double GetRotationFromPID(double p, double i, double d);
  double LimitMaxTurnSpeed(double currentSpeed);

  bool isComplete;
  static double targetAngle;
  double totalTargetAngle = 0;
  double currentAngle;
  int defaultPeriodInMs = 20;

  const double pValue = 1.3;
  const double iValue = 0;
  const double dValue = 0;

  const double maxTurnSpeed = 0.5;
  const double minError = 0.05;
  double error = 0;
  double errorPrior = 0;
  double integral = 0;
  double derivative = 0;
};