/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/AIVisionTargetting.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <string>
#include <memory>

#include "Constants.h"
#include "RobotContainer.h"

using Target = AIVisionTargetting::Target;

bool IsXInRange(unsigned x, unsigned low, unsigned high) {
    return ((x - low) <= (high - low));
}

AIVisionTargetting::AIVisionTargetting() {
    centerTriangle = GetCenterTriangle();
 }

// This method will be called once per scheduler run
void AIVisionTargetting::Periodic() {
    pcOffsetInCam = RobotContainer::aiComms->GetPCOffsetInCameraX();
    RegisterFoundTargets();
}

bool AIVisionTargetting::CheckForTarget(Target type) {
    bool isTargetTypeFound = false;
    if (RobotContainer::aiComms->IsTargetFound()) {
        if (type == CheckTargetType())
            isTargetTypeFound = true;
    }
    else
        isTargetTypeFound = false;

    return isTargetTypeFound;
}

Target AIVisionTargetting::CheckTargetType() {
    std::string targetType = frc::SmartDashboard::GetString("targetType:", "pc");
    if (targetType == "pc")
        return Target::Powercell;
    else if (targetType == "goal")
        return Target::Goal;
    else
        return Target::None;
}

int AIVisionTargetting::TimeSinceTargetRegisteredInMillis() {
    int multiplier = 20;
    int millis = loopCyclesSinceTargetRegistered * multiplier;
    return millis;
}

bool AIVisionTargetting::IsTargetLocked() {
    bool isTargetFound = RobotContainer::aiComms->IsTargetFound();
    int currentPan = RobotContainer::cameraMount->GetCurrentPan();
    int avgOfRecentPans = RobotContainer::cameraMount->GetAvgOfRecentPans();

    return (IsXInRange(currentPan, avgOfRecentPans-3, avgOfRecentPans+3) and isTargetFound);
}

double AIVisionTargetting::GetRobotDistToTarget() {
    mainTriangle = GetMainTriangle();
    double calculatedDist = 0;

    try {
        calculatedDist = GetMainTriangle()->GetSideB();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }
    return calculatedDist;
}

double AIVisionTargetting::GetRobotAngleToTarget() {
    double calculatedAngle = 0;

    try {
        // // calculatedAngle = precisionTriangle.GetAngleB();
        // calculatedAngle = precisionTriangle.GetAngleA() - 30;
        calculatedAngle = finalTriangle->GetAngleC();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }
    // return (-1*(calculatedAngle - servoToRobotCenterAngleOffset));
    return calculatedAngle;
}

double AIVisionTargetting::GetCameraDistToTargetFromArea(int area) {
    // pwr. reg. equation determined from sample bounding box areas at several intervals
    double dist = (3349.276088 * pow(area, -0.5003571008));
    return dist;
}

int AIVisionTargetting::GetArea() {
    return RobotContainer::aiComms->GetNumber("target area");
}

void AIVisionTargetting::RegisterFoundTargets() {

    if (RobotContainer::aiComms->IsTargetFound() && !targetHasBeenRegistered) {
        loopCyclesSinceTargetRegistered = 0;
        targetHasBeenRegistered = true;
    }
    else {
        loopCyclesSinceTargetRegistered++;
        if (!RobotContainer::aiComms->IsTargetFound())
            targetHasBeenRegistered = false;
    }
}

std::unique_ptr<Triangle> AIVisionTargetting::GetMainTriangle() {
    // uppercase and lowercase letters follow standard triangle naming (such as in law of cosines form, etc.)
    double a_1 = GetCameraDistToTargetFromArea(GetArea());
    double c_1 = centerTriangle->GetSideB();
    double B_1 = 180 - RobotContainer::cameraMount->GetCurrentPan() + pcOffsetInCam;

    std::unique_ptr<Triangle> rawTriangle = std::make_unique<Triangle>(a_1, 0, c_1, 0, B_1, 0);
    calculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return calculator->SAS();
}

std::unique_ptr<Triangle> AIVisionTargetting::GetPrecisionTriangle() {
    mainTriangle = GetMainTriangle();

    double a_2 = mainTriangle->GetSideA();
    double c_2 = centerTriangle->GetSideA();
    double B_2 = mainTriangle->GetAngleA() + centerTriangle->GetAngleB();

    std::unique_ptr<Triangle> rawTriangle = std::make_unique<Triangle>(a_2, 0, c_2, 0, B_2, 0);
    calculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return calculator->SAS();
}

std::unique_ptr<Triangle> AIVisionTargetting::GetComplementaryMainTriangle() {
    mainTriangle = GetMainTriangle();
    
    double b_3 = mainTriangle->GetSideB();
    double c_3 = mainTriangle->GetSideC();
    double A_3 = 90 - mainTriangle->GetAngleC();

    auto rawTriangle = std::make_unique<Triangle>(0, b_3, c_3, A_3, 0, 0);
    calculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return calculator->SAS();
}

std::unique_ptr<Triangle> AIVisionTargetting::GetFinalTriangle() {
    complementaryTriangle = GetComplementaryMainTriangle();
    precisionTriangle = GetPrecisionTriangle();

    double a_4 = centerTriangle->GetSideC() + complementaryTriangle->GetSideB();
    double b_4 = precisionTriangle->GetSideB();
    double c_4 = complementaryTriangle->GetSideC();

    auto rawTriangle = std::make_unique<Triangle>(a_4, b_4, c_4, 0, 0, 0);
    calculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return calculator->SSS();
}

std::unique_ptr<Triangle> AIVisionTargetting::GetCenterTriangle() {
    double a = Constants::camDistFromRoboCenter;
    double b = 8.5;
    double c = 12;

    auto rawTriangle = std::make_unique<Triangle>(a, b, c, 0, 0, 0);
    calculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return calculator->SSS();
}