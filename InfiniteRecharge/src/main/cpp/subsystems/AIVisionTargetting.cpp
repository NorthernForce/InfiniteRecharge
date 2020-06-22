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

#include "RobotContainer.h"
#include "Constants.h"
#include "utilities/TriangleCalculator.h"
#include "utilities/Triangle.h"

using Target = AIVisionTargetting::Target;

AIVisionTargetting::AIVisionTargetting() {}

// This method will be called once per scheduler run
void AIVisionTargetting::Periodic() {}

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

int AIVisionTargetting::GetArea() {
    return RobotContainer::aiComms->GetNumber("target area");
}

double AIVisionTargetting::GetCameraDistToTargetFromArea(int area) {
    // pwr. reg. equation determined from sample bounding box areas at several intervals
    double num = (3349.276088 * pow(area, -0.5003571008));
    frc::SmartDashboard::PutNumber("powercell dist.", num);
    return num;
}

double AIVisionTargetting::GetRobotAngleToTarget() {
    // uppercase and lowercase letters follow standard triangle naming (such as in law of cosines form, etc.)
    double calculatedAngle;
    double pcOffsetInCam = RobotContainer::aiComms->GetCamTargetOffsets(powercell)[0];
    double a = GetCameraDistToTargetFromArea(GetArea());
    double c = Constants::camDistFromRoboCenter;
    double B = 180 - RobotContainer::cameraMount->GetCurrentPan() + pcOffsetInCam; // replace 90 with the correct angle

    auto rawTriangle = std::make_unique<Triangle>(a, 0, c, 0, B, 0);
    auto angleCalc = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    
    try {
        calculatedAngle = angleCalc->SAS().GetAngleA();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }
    frc::SmartDashboard::PutNumber("angle to target", calculatedAngle);
    return (calculatedAngle - 90);
}

bool AIVisionTargetting::IsTargetCentered() {
    bool isCentered;
    double targetOffset = RobotContainer::aiComms->GetCamTargetOffsets(powercell)[0];
    if (!CheckForTarget())
        isCentered = false;
    else if (CheckForTarget() && abs(targetOffset) < 5)
        isCentered = true;
    
    return isCentered;
}