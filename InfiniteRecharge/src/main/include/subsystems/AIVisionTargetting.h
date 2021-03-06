/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
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
    int TimeSinceTargetRegisteredInMillis();
    bool IsTargetLocked();
    std::pair<double, double> GetFieldCoordinatesOfTarget();
    double GetCenterRobotDistToTarget();
    double GetRobotAngleToTarget();    

 private:
    bool CheckForTarget(Target type=Target::Powercell);
    Target CheckTargetType();
    double GetCameraDistToTarget();
    double GetRobotAngleToTargetIntakeCam();
    char GetSideOfIntakeWithTargetFromMainCam();
    char GetSideOfIntakeWithTargetFromIntakeCam();
    double GetCameraDistToTargetFromArea(int area);
    int GetArea();
    void RegisterFoundTargets();
    Triangle GetMainTriangle();
    Triangle GetRightHelperTriangle();
    Triangle GetRightFinalTriangle();
    Triangle GetLeftFinalTriangle();
    Triangle GetFinalTriangle();
    Triangle GetCenterTriangle();
    double GetPowercellOffsetInIntakeCam();
    Triangle GetIntakeTriangle();
    Triangle CalculateTriangle(std::unique_ptr<Triangle> rawTriangle, std::string calcMethod);
    double GetHeightOfTriangle(Triangle t, double base);

    Triangle mainTriangle;
    Triangle rightHelperTriangle;
    Triangle finalTriangle;
    Triangle centerTriangle;

    std::unique_ptr<TriangleCalculator> calculator;

    double camAngleOffset;
    int servoToRobotCenterAngleOffset = 90;
    double pcOffsetInCam;

    int loopCyclesSinceTargetRegistered;
    bool targetHasBeenRegistered;
};
