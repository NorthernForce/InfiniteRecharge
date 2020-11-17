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
    frc::SmartDashboard::PutNumber("distanceToTarget", GetCameraDistToTargetFromArea(GetArea()));
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

std::pair<double, double> AIVisionTargetting::GetFieldCoordinatesOfTarget() {
    double distance = GetRobotDistToTarget();
    double robotCurrentAngle = RobotContainer::imu->GetRotation();
    double angle = robotCurrentAngle + GetRobotAngleToTarget();
    double currentX = RobotContainer::navigation->GetCoordinatePosition().first;
    double currentY = RobotContainer::navigation->GetCoordinatePosition().second;
    double x = (distance * cos(angle * Constants::degreesToRadians)) + currentX;
    double y = -(distance * sin(angle * Constants::degreesToRadians)) + currentY;
    return std::make_pair(x, y);
}

double AIVisionTargetting::GetRobotDistToTarget() {
    mainTriangle = GetMainTriangle();
    double calculatedDist = 0;

    try {
        calculatedDist = mainTriangle.GetSideB();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }
    return calculatedDist;
}

double AIVisionTargetting::GetRobotAngleToTarget() {
    double calculatedAngle = 0;
    char sideOfIntakeWithTarget = GetSideOfIntakeWithTargetFromMainCam();
    finalTriangle = GetFinalTriangle();

    try {
        calculatedAngle = finalTriangle.GetAngleB();
        if (sideOfIntakeWithTarget == 'l')
            calculatedAngle *= -1;
        else
            calculatedAngle *= 1.2;
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }
    return calculatedAngle;
}

double AIVisionTargetting::GetRobotAngleToTargetIntakeCam() {
    double calculatedAngle = 0;
    char sideOfIntakeWithTarget = GetSideOfIntakeWithTargetFromIntakeCam();
    Triangle intakeTriangle = GetIntakeTriangle();

    try {
        calculatedAngle = intakeTriangle.GetAngleB();
        if (sideOfIntakeWithTarget == 'l')
            calculatedAngle *= -1;
        else if (sideOfIntakeWithTarget == 'c')
            calculatedAngle = 0;
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
    }

    return calculatedAngle;
}

char AIVisionTargetting::GetSideOfIntakeWithTargetFromMainCam() {
    double angFromIntakeCenter = GetMainTriangle().GetAngleA();
    double servoPan = RobotContainer::cameraMount->GetCurrentPan();
    frc::SmartDashboard::PutNumber("servo pan", servoPan);

    if (angFromIntakeCenter < 90 || servoPan < 90)
        return 'r';
    else if (angFromIntakeCenter > 90)
        return 'l';
    else
        return 'c';
}

char AIVisionTargetting::GetSideOfIntakeWithTargetFromIntakeCam() {
    double xCoord = frc::SmartDashboard::GetNumber("AI: IntakeOffsetX", 0);
    double x_max = 205;
    double x_min = 165;

    if (xCoord < x_max)
        return 'l';
    else if (xCoord > x_min)
        return 'r';
    else
        return 'c';
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
    double a = GetCameraDistToTargetFromArea(GetArea());
    double c = centerTriangle.GetSideB();
    double B = 180 - RobotContainer::cameraMount->GetCurrentPan() + pcOffsetInCam;

    std::unique_ptr<Triangle> rawTriangle = std::make_unique<Triangle>(a, 0, c, 0, B, 0);
    return CalculateTriangle(std::move(rawTriangle), "SAS");
}

Triangle AIVisionTargetting::GetRightHelperTriangle() {
    mainTriangle = GetMainTriangle();

    double a = mainTriangle.GetSideA();
    double c = GetHeightOfTriangle(mainTriangle, mainTriangle.GetSideC());
    double B = 90 - mainTriangle.GetAngleA();

    std::unique_ptr<Triangle> rawTriangle = std::make_unique<Triangle>(a, 0, c, 0, B, 0);
    return CalculateTriangle(std::move(rawTriangle), "SAS");
}

Triangle AIVisionTargetting::GetRightFinalTriangle() {
    std::unique_ptr<Triangle> rawTriangle;
    double b, c, a;
    rightHelperTriangle = GetRightHelperTriangle();

    b = rightHelperTriangle.GetSideB();
    c = rightHelperTriangle.GetSideC() + centerTriangle.GetSideC();
    a = sqrt(pow(b, 2) + pow(c, 2));

    rawTriangle = std::make_unique<Triangle>(a, b, c, 0, 0, 0);
    
    return CalculateTriangle(std::move(rawTriangle), "SSS");
}

Triangle AIVisionTargetting::GetLeftFinalTriangle() {
    std::unique_ptr<Triangle> rawTriangle;
    double b, c, A;
    mainTriangle = GetMainTriangle();

    b = mainTriangle.GetSideB();
    c = centerTriangle.GetSideC();
    A = 360 - (centerTriangle.GetAngleA() + mainTriangle.GetAngleA());

    rawTriangle = std::make_unique<Triangle>(0, b, c, A, 0, 0);
    return CalculateTriangle(std::move(rawTriangle), "SAS");
}

Triangle AIVisionTargetting::GetFinalTriangle() {
    char turnDir = GetSideOfIntakeWithTargetFromMainCam();
        
    if (turnDir == 'l')
        finalTriangle = GetLeftFinalTriangle();
    else if (turnDir == 'r')
        finalTriangle = GetRightFinalTriangle();

    return finalTriangle;
}

Triangle AIVisionTargetting::GetCenterTriangle() {
    double a = Constants::camDistFromRoboCenter;
    double b = 8.5;
    double c = 12;

    auto rawTriangle = std::make_unique<Triangle>(a, b, c, 0, 0, 0);
    return CalculateTriangle(std::move(rawTriangle), "SSS");
}

double AIVisionTargetting::GetPowercellOffsetInIntakeCam() {
    int px_per_inch = 40;
    int x_intake_center = 185;
    double xCoord = frc::SmartDashboard::GetNumber("AI: IntakeOffsetX", 0);
    
    double xError = x_intake_center - xCoord;
    double pcOffsetInches = xError / px_per_inch;
    return pcOffsetInches;
}

Triangle AIVisionTargetting::GetIntakeTriangle() {
    std::unique_ptr<Triangle> rawTriangle;
    double b, c, A;

    b = GetPowercellOffsetInIntakeCam();
    c = Constants::intakeDistFromRoboCenter;
    A = 90;

    rawTriangle = std::make_unique<Triangle>(0, b, c, A, 0, 0);
    return CalculateTriangle(std::move(rawTriangle), "SAS");
}

Triangle AIVisionTargetting::CalculateTriangle(std::unique_ptr<Triangle> rawTriangle, std::string calcMethod) {
    Triangle finishedTriangle;

    try {
        auto calculator = std::make_unique<TriangleCalculator>(std::move(rawTriangle));
        if (calcMethod == "SAS")
            finishedTriangle = calculator->SAS();
        else if (calcMethod == "SSS")
            finishedTriangle = calculator->SSS();
    }
    catch (const TriangleCalculator::BaseException& e) {
        std::cout << e.what() << '\n';
        std::cout << "Angles: " << finishedTriangle.GetAngleA() << ", " << finishedTriangle.GetAngleB() << ", " << finishedTriangle.GetAngleC() << '\n';
    }
    return finishedTriangle;
}

double AIVisionTargetting::GetHeightOfTriangle(Triangle t, double base) {
    double a = t.GetSideA();
    double b = t.GetSideB();
    double c = t.GetSideC();
    double s = (a + b + c) / 2;

    double area = sqrt(s * (s-a) * (s-b) * (s-c));
    double height = (2 * area) / base;

    return height;
}

char AIVisionTargetting::GetPrecisePowercellSideOfIntake() {
    RobotContainer::cameraMount->Pan(110);
    double x = RobotContainer::aiComms->GetPCOffsetInCameraX();
    double y = RobotContainer::aiComms->GetPCOffsetInCameraY();

    double lineX = 0.33*y - 211.11;
    
    if (x > lineX)
        return 'l';
    else if (x < lineX)
        return 'r';
    else
        return 'c';
}