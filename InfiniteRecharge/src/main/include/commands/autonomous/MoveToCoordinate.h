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
#include <memory>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveToCoordinate
    : public frc2::CommandHelper<frc2::CommandBase, MoveToCoordinate> {
 public:
  MoveToCoordinate(int xPos, int yPos, double speed=0.3);

  void Initialize() override;

  // double RemoveJumps(double angToFinalWithJumps);
  double Limit(double value, double limit);
  double TurnPID();
  double DrivePID();

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;


  std::unique_ptr<TurnToAngle> turnToAngle;

  int xFinal;
  int yFinal;
  const double baseSpeed;

  const int cyclePerSecond = 20;

  double angleError;
  double totalAngleError;
  double distanceError;
  double totalDistanceError;
  double previousDistanceError;

  double xCurrent;
  double yCurrent;
  double angToFinal;
  double distance;

  double turnSpeed;
  double driveSpeed;

  std::vector<double> previousAngToFinals;

  double leftPower;
  double rightPower;

  int movementStage;

  int finishCounter = 0;
};
