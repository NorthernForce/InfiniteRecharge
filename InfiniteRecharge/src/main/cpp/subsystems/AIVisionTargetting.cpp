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
    frc::SmartDashboard::PutNumber("avgOfRecentPans", avgOfRecentPans);
    frc::SmartDashboard::PutNumber("currentPan", currentPan);
    return (IsXInRange(avgOfRecentPans-3, avgOfRecentPans+3, currentPan) and isTargetFound);
}

double AIVisionTargetting::GetRobotDistToTarget() {
    double calculatedDist = 0;

    try {
        calculatedDist = GetMainTriangle().GetSideB();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }
    return calculatedDist;
}

double AIVisionTargetting::GetRobotAngleToTarget() {
    double calculatedAngle = 0;

    try {
        // calculatedAngle = GetPrecisionTriangle().GetAngleB();
        calculatedAngle = GetPrecisionTriangle().GetAngleA() - 30;
        calculatedAngle = GetFinalTriangle().GetAngleC();
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

Triangle AIVisionTargetting::GetMainTriangle() {
    // uppercase and lowercase letters follow standard triangle naming (such as in law of cosines form, etc.)
    double a_1 = GetCameraDistToTargetFromArea(GetArea());
    double c_1 = centerTriangle.GetSideB();
    double B_1 = 180 - RobotContainer::cameraMount->GetCurrentPan() + pcOffsetInCam;

    std::unique_ptr<Triangle> rawTriangle = std::make_unique<Triangle>(a_1, 0, c_1, 0, B_1, 0);
    std::unique_ptr<TriangleCalculator> mainCalculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return mainCalculator->SAS();
}

Triangle AIVisionTargetting::GetPrecisionTriangle() {
    auto mainTriangle = GetMainTriangle();

    double a_2 = mainTriangle.GetSideA();
    double c_2 = 12.5;
    double B_2 = mainTriangle.GetAngleA() + centerTriangle.GetAngleB();

    std::unique_ptr<Triangle> rawTriangle = std::make_unique<Triangle>(a_2, 0, c_2, 0, B_2, 0);
    std::unique_ptr<TriangleCalculator> precisionCalculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return precisionCalculator->SAS();
}

Triangle AIVisionTargetting::GetComplementaryMainTriangle() {
    auto mainTriangle = GetMainTriangle();
    
    double b_3 = mainTriangle.GetSideB();
    double c_3 = mainTriangle.GetSideC();
    double A_3 = 90 - mainTriangle.GetAngleC();

    auto rawTriangle = std::make_unique<Triangle>(0, b_3, c_3, A_3, 0, 0);
    std::unique_ptr<TriangleCalculator> complementaryCalculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return complementaryCalculator->SAS();
}

Triangle AIVisionTargetting::GetFinalTriangle() {
    auto complementaryTriangle = GetComplementaryMainTriangle();
    auto precisionTriangle = GetPrecisionTriangle();

    double a_4 = centerTriangle.GetSideC() + complementaryTriangle.GetSideB();
    double b_4 = precisionTriangle.GetSideB();
    double c_4 = complementaryTriangle.GetSideC();

    auto rawTriangle = std::make_unique<Triangle>(a_4, b_4, c_4, 0, 0, 0);
    std::unique_ptr<TriangleCalculator> finalTriangleCalc = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    return finalTriangleCalc->SSS();
}

Triangle AIVisionTargetting::GetCenterTriangle() {
    double a = 12.5; //Constants::camDistFromRoboCenter;
    double b = 8.5; //9;
    double c = 12; //16;

    auto triangle = std::make_unique<Triangle>(a, b, c, 0, 0, 0);
    std::unique_ptr<TriangleCalculator> centerTriangleCalc = std::make_unique<TriangleCalculator>(std::move(triangle));
    return centerTriangleCalc->SSS();
}