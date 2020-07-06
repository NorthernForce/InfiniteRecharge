/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#include <rev/CANSparkMax.h>

class Navigation : public frc2::SubsystemBase {
 public:
  Navigation();
  void Periodic();
  std::pair<double, double> GetInchesTravelled();
  void ResetPosition();
  void ZeroPosition();
  void ZeroAngle();
  void CoordinatePosition();
  std::pair<double, double> GetCoordinatePosition();

 private:
    double robotStartingAngle;
    double robotCurrentAngle;
    double robotAngleDifference = robotStartingAngle - robotCurrentAngle;
    double cameraStartingAngle;
    double cameraCurrentAngle;
    double cameraAngleDifference = cameraStartingAngle - cameraCurrentAngle;
    double previousLeftEncoder = 0;
    double previousRightEncoder = 0;

    double averageSpeedInRPM;
    double totalDistanceTravelled;
    double lastDistanceTravelled;

    double xPosition;
    double yPosition;
    double NavXScaling = Constants::XResetMultiplier;

    // const double cameraOffsetFromCenter;
    double distanceToObstacle;
};
