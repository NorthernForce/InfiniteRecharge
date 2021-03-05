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
#include "commands/autonomous/AvoidObstacles.h"
#include "Constants.h"

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

  double avoidAmount;
};

namespace CPlane {
    class Point {
        public:
        double x,y;
        Point(double x, double y)
        : x(x), y(y) {}
    };

    const Point A1 = Point(30,150);
    const Point A2 = Point(60,150);
    const Point A3 = Point(90,150);
    const Point A4 = Point(120,150);
    const Point A5 = Point(150,150);
    const Point A6 = Point(180,150);
    const Point A7 = Point(210,150);
    const Point A8 = Point(240,150);
    const Point A9 = Point(270,150);
    const Point A10 = Point(300,150);
    const Point A11 = Point(330,150);

    const Point B1 = Point(30,120);
    const Point B2 = Point(60,120);
    const Point B3 = Point(90,120);
    const Point B4 = Point(120,120);
    const Point B5 = Point(150,120);
    const Point B6 = Point(180,120);
    const Point B7 = Point(210,120);
    const Point B8 = Point(240,120);
    const Point B9 = Point(270,120);
    const Point B10 = Point(300,120);
    const Point B11 = Point(330,120);

    const Point C1 = Point(30,90);
    const Point C2 = Point(60,90);
    const Point C3 = Point(90,90);
    const Point C4 = Point(120,90);
    const Point C5 = Point(150,90);
    const Point C6 = Point(180,90);
    const Point C7 = Point(210,90);
    const Point C8 = Point(240,90);
    const Point C9 = Point(270,90);
    const Point C10 = Point(300,90);
    const Point C11 = Point(330,90);

    const Point D1 = Point(30,60);
    const Point D2 = Point(60,60);
    const Point D3 = Point(90,60);
    const Point D4 = Point(120,60);
    const Point D5 = Point(150,60);
    const Point D6 = Point(180,60);
    const Point D7 = Point(210,60);
    const Point D8 = Point(240,60);
    const Point D9 = Point(270,60);
    const Point D10 = Point(300,60);
    const Point D11 = Point(330,60);

    const Point E1 = Point(30,30);
    const Point E2 = Point(60,30);
    const Point E3 = Point(90,30);
    const Point E4 = Point(120,30);
    const Point E5 = Point(150,30);
    const Point E6 = Point(180,30);
    const Point E7 = Point(210,30);
    const Point E8 = Point(240,30);
    const Point E9 = Point(270,30);
    const Point E10 = Point(300,30);
    const Point E11 = Point(330,30);
}

  static std::shared_ptr<MoveToCoordinate> moveToCoordinate;
