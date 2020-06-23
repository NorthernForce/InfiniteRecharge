/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <memory>
#include "utilities/TriangleCalculator.h"

class AIVisionTargetting : public frc2::SubsystemBase {
 public:
    enum class Target {
        Powercell,
        Goal,
        None
    };
    AIVisionTargetting();
    void Periodic();
    bool CheckForTarget(Target type=Target::Powercell);
    Target CheckTargetType();
    bool IsTargetCentered();
    double GetRobotAngleToTarget();
    double GetAngleAFromCalculator(std::unique_ptr<TriangleCalculator> calculator);
    double GetCameraDistToTargetFromArea(int area);
    int GetArea();

 private:
    double camAngleOffset;
    int servoToRobotCenterAngleOffset = 90;
    double pcOffsetInCam;
};
