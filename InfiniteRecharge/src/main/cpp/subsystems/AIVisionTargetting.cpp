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

AIVisionTargetting::AIVisionTargetting() {
}

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

double AIVisionTargetting::GetCameraDistToTarget() {
    // remember to fill this in
}

double AIVisionTargetting::GetAngleToTarget() {
    // uppercase and lowercase letters follow standard triangle naming for law of cosines
    double a = GetCameraDistToTarget(); // exp reg eq for getting target
    double c = Constants::camDistFromRoboFrontCent;
    double B = RobotContainer::cameraMount->GetCurrentPan();

    auto rawTriangle = std::make_unique<Triangle>(a, 0, c, 0, B, 0);
    auto angleCalc = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
    
    double angleToTarget = angleCalc->SAS().GetAngleA();
    frc::SmartDashboard::PutNumber("angleToTarget", angleToTarget) - 90;
    return angleToTarget;
}