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
#include "utilities/CPlane.h"
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
  MoveToCoordinate(CPlane::Point end, double speed=0.3);

  void Initialize() override;

  // double RemoveJumps(double angToFinalWithJumps);
  double Limit(double value, double limit);

  void AvoidRedirection(double correctionAmount);

  double TurnPID();

  void Set(std::vector<double>pidValues); //Sets drive pid values

  double DrivePID();

  bool HasOscillated();

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  std::unique_ptr<TurnToAngle> turnToAngle;

  CPlane::Point finalPos;
  const double baseSpeed;

  const int cyclePerSecond = 20;

  std::vector<double>driveValues = {0.245, 0.002, 0.002};

  double angleError;
  double totalAngleError;
  double distanceError;
  double totalDistanceError;
  double previousDistanceError;

  CPlane::Point robotPos;
  double angToFinal;
  double distance;

  double turnSpeed;
  double driveSpeed;

  bool hasOscillated;

  std::vector<double> previousAngToFinals;
  std::vector<double> averageLeft;
  std::vector<double> averageRight;

  double leftPower;
  double rightPower;

  int movementStage;

  int finishCounter = 0;

  double avoidAmount = 0 ;
};