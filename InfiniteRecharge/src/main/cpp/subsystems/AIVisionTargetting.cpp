/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/AIVisionTargetting.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <string>

#include "Constants.h"
#include "utilities/TriangleCalculator.h"
#include "utilities/Triangle.h"
#include "RobotContainer.h"

using Target = AIVisionTargetting::Target;

AIVisionTargetting::AIVisionTargetting() {}

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

bool AIVisionTargetting::IsTargetCentered() {
    bool isCentered = false;
    if (!CheckForTarget())
        isCentered = false;
    else if (CheckForTarget() && abs(pcOffsetInCam) < 5)
        isCentered = true;
    
    return isCentered;
}

double AIVisionTargetting::GetRobotAngleToTarget() {
    // uppercase and lowercase letters follow standard triangle naming (such as in law of cosines form, etc.)
    double a = GetCameraDistToTargetFromArea(GetArea());
    double c = Constants::camDistFromRoboCenter;
    double B = 180 - RobotContainer::cameraMount->GetCurrentPan() + pcOffsetInCam;

    auto inputTriangle = std::make_unique<Triangle>(a, 0, c, 0, B, 0);
    auto calculator = std::make_unique<TriangleCalculator>(std::move(inputTriangle));

    double calculatedAngle = GetAngleAFromCalculator(std::move(calculator));
    return calculatedAngle;
}

double AIVisionTargetting::GetAngleAFromCalculator(std::unique_ptr<TriangleCalculator> calculator) {
    double calculatedAngle = 0;
    try {
        calculatedAngle = calculator->SAS().GetAngleA();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }

    return (-1*(calculatedAngle - 90));
}

double AIVisionTargetting::GetCameraDistToTargetFromArea(int area) {
    // pwr. reg. equation determined from sample bounding box areas at several intervals
    double num = (3349.276088 * pow(area, -0.5003571008));
    frc::SmartDashboard::PutNumber("powercell dist.", num);
    return num;
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