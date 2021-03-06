/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "commands/autonomous/MoveToCoordinate.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TuneValue
    : public frc2::CommandHelper<frc2::CommandBase, TuneValue> {
 public:
  TuneValue(int valueToTune, std::vector<double> parameters, std::vector<double> pidValues, double increment = 0.1, double accuracy = 0.01);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  int tunedValue;
  std::unique_ptr<MoveToCoordinate> commandToTune;
  std::vector<double> commandToTuneParams;
  std::vector<double>values;
  double tuneIncremenet;
  double tuneAccuracy;
  bool scheduleCommand = true;
  int commandFail;
};
