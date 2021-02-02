/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include "commands/TurnToTarget.h"
#include "commands/autonomous/MoveToCoordinate.h"
#include "commands/IntakePowerCell.h"
#include "commands/TurnToAngle.h"
#include <memory>

class AutoBallSeek
    : public frc2::CommandHelper<frc2::CommandBase, AutoBallSeek> {
 public:
  AutoBallSeek();
  void Initialize() override;
  void Execute() override;
  void SetDistanceToTargetAndDrive();
  double CalculateMedian(std::vector<double> array);
  void DriveToTargetAndStop();
  void End(bool interrupted) override;
  bool IsFinished() override;

 private:
    std::unique_ptr<TurnToTarget> turnToTarget = std::make_unique<TurnToTarget>();
    std::unique_ptr<TurnToAngle> turnToAngle = std::make_unique<TurnToAngle>();
    std::unique_ptr<MoveToCoordinate> moveToCoordinate;
    std::unique_ptr<IntakePowerCell> intakeBall = std::make_unique<IntakePowerCell>();
    std::unique_ptr<frc::Timer> timer;

    double inchesToTarget = 0;
    std::vector<double> anglesToTarget;
    bool hasTurned = false;
    bool hasDriven = false;
    bool distHasBeenSet = false;
    bool driveHasBeenScheduled = false;
    bool intakeHasBeenScheduled = false;
    bool turnToAngleHasBeenScheduled = false;
    bool timerHasStarted = false;
};