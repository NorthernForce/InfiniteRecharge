/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "commands/TurnToTarget.h"
#include "commands/AutoDrive.h"
#include "commands/IntakePowerCell.h"
#include <memory>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoBallSeek
    : public frc2::CommandHelper<frc2::CommandBase, AutoBallSeek> {
 public:
  AutoBallSeek();
  void DriveToTarget();
  void Initialize() override;
  void Execute() override;
  void End(bool interrupted) override;
  bool IsFinished() override;

 private:
    std::unique_ptr<TurnToTarget> turnToTarget = std::make_unique<TurnToTarget>();
    std::unique_ptr<AutoDrive> autoDrive = std::make_unique<AutoDrive>();
    std::unique_ptr<IntakePowerCell> intakeBall = std::make_unique<IntakePowerCell>();
    double distToTarget;
    bool isTargetLocked = false;
    bool distHasBeenSet = true;
    bool hasDriven = false;
    bool hasCompletedIntake = false;
};
