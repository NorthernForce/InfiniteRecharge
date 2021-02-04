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
  MoveToCoordinate(double xPos, double yPos, double speed=0.3);

  void Initialize() override;

  // double RemoveJumps(double angToFinalWithJumps);
  double Limit(double value, double limit);

  double TurnPID();

  void Set(std::vector<double>pidValues); //Sets drive pid values

  double DrivePID();

  bool HasOscillated();

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  std::unique_ptr<TurnToAngle> turnToAngle;

  double xFinal;
  double yFinal;
  const double baseSpeed;

  const int cyclePerSecond = 20;

  std::vector<double>driveValues = {0.245, 0.002, 0.002};

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

  bool hasOscillated;

  std::vector<double> previousAngToFinals;
  std::vector<double> averageLeft;
  std::vector<double> averageRight;

  double leftPower;
  double rightPower;

  int movementStage;

  int finishCounter = 0;


};

namespace CoordinatePlane {
  auto A1 = std::make_pair(30,150);
  auto A2 = std::make_pair(60,150);
  auto A3 = std::make_pair(90,150);
  auto A4 = std::make_pair(120,150);
  auto A5 = std::make_pair(150,150);
  auto A6 = std::make_pair(180,150);
  auto A7 = std::make_pair(210,150);
  auto A8 = std::make_pair(240,150);
  auto A9 = std::make_pair(270,150);
  auto A10 = std::make_pair(300,150);
  auto A11 = std::make_pair(330,150);

  auto B1 = std::make_pair(30,120);
  auto B2 = std::make_pair(60,120);
  auto B3 = std::make_pair(90,120);
  auto B4 = std::make_pair(120,120);
  auto B5 = std::make_pair(150,120);
  auto B6 = std::make_pair(180,120);
  auto B7 = std::make_pair(210,120);
  auto B8 = std::make_pair(240,120);
  auto B9 = std::make_pair(270,120);
  auto B10 = std::make_pair(300,120);
  auto B11 = std::make_pair(330,120);

  auto C1 = std::make_pair(30,90);
  auto C2 = std::make_pair(60,90);
  auto C3 = std::make_pair(90,90);
  auto C4 = std::make_pair(120,90);
  auto C5 = std::make_pair(150,90);
  auto C6 = std::make_pair(180,90);
  auto C7 = std::make_pair(210,90);
  auto C8 = std::make_pair(240,90);
  auto C9 = std::make_pair(270,90);
  auto C10 = std::make_pair(300,90);
  auto C11 = std::make_pair(330,90);

  auto D1 = std::make_pair(30,60);
  auto D2 = std::make_pair(60,60);
  auto D3 = std::make_pair(90,60);
  auto D4 = std::make_pair(120,60);
  auto D5 = std::make_pair(150,60);
  auto D6 = std::make_pair(180,60);
  auto D7 = std::make_pair(210,60);
  auto D8 = std::make_pair(240,60);
  auto D9 = std::make_pair(270,60);
  auto D10 = std::make_pair(300,60);
  auto D11 = std::make_pair(330,60);

  auto E1 = std::make_pair(30,30);
  auto E2 = std::make_pair(60,30);
  auto E3 = std::make_pair(90,30);
  auto E4 = std::make_pair(120,30);
  auto E5 = std::make_pair(150,30);
  auto E6 = std::make_pair(180,30);
  auto E7 = std::make_pair(210,30);
  auto E8 = std::make_pair(240,30);
  auto E9 = std::make_pair(270,30);
  auto E10 = std::make_pair(300,30);
  auto E11 = std::make_pair(330,30);
}
