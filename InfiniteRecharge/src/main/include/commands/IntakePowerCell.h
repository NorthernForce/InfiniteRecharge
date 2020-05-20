/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

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
class IntakePowerCell
    : public frc2::CommandHelper<frc2::CommandBase, IntakePowerCell> {
 public:
  IntakePowerCell();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  int emptyPosition;
  int conveyorBackwardsCounter = 0;
  const int backwardCountLimit = 2;

  //position four sensor was too high up, in order to stop cells faster we made it based on pos 0 clearing
  bool zeroHasBeenTriggered; 
  bool oneTriggered;
  bool emptyPositionTriggered = false;
  bool fiveReached = false;


};
