/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"

class Navigation : public frc2::SubsystemBase {
 public:
  Navigation();
  void Periodic();
  std::pair<double, double> GetInchesTravelled();

 private:
    double robotStartingAngle;
    double robotCurrentAngle;
    double robotAngleDifference = robotStartingAngle - robotCurrentAngle;
    double cameraStartingAngle;
    double cameraCurrentAngle;
    double cameraAngleDifference = cameraStartingAngle - cameraCurrentAngle;

    double averageSpeedInRPM;
    double totalDistanceTravelled;
    double lastDistanceTravelled;

    // const double cameraOffsetFromCenter;
    const std::pair<double, double> currentLocation;
    double distanceToObstacle;
};