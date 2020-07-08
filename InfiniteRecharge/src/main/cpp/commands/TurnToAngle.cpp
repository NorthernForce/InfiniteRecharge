/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToAngle.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/TimedRobot.h>
#include "RobotContainer.h"

double TurnToAngle::targetAngle;

TurnToAngle::TurnToAngle(double target) {
    SetName("TurnToAngle");
    AddRequirements(RobotContainer::drivetrain.get());
    AddRequirements(RobotContainer::imu.get());

    frc::SmartDashboard::PutNumber("TurnToAngle: P", pValue);
    frc::SmartDashboard::PutNumber("TurnToAngle: I", iValue);
    frc::SmartDashboard::PutNumber("TurnToAngle: D", dValue);

    if (target != 0)
        SetAngle(target);
}

void TurnToAngle::SetAngle(double angle) {
    targetAngle = angle;
}

// Called when the command is initially scheduled.
void TurnToAngle::Initialize() {
    currentAngle = RobotContainer::imu->GetRotation();
    distanceToTargetAngle = currentAngle + targetAngle;
    integral = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnToAngle::Execute() {
    currentAngle = RobotContainer::imu->GetRotation();
    frc::SmartDashboard::PutNumber("Robot angle: ", currentAngle);

    double p = frc::SmartDashboard::GetNumber("TurnToAngle: P", pValue);
    double i = frc::SmartDashboard::GetNumber("TurnToAngle: I", iValue);
    double d = frc::SmartDashboard::GetNumber("TurnToAngle: D", dValue);

    double rotRaw = GetRotationFromPID(p,i,d);
    double rotMult = GetRotationMultiplier();
    double rotLim = LimitMaxTurnSpeed(rotRaw * rotMult);
    frc::SmartDashboard::PutNumber("rotation multiplier:", rotMult);
    
    auto driveControls = RobotContainer::oi->GetDriveControls();
    RobotContainer::drivetrain->Drive(driveControls.first, rotLim + driveControls.second * 0.5);
}

double TurnToAngle::GetRotationFromPID(double p, double i, double d) {
    error = (currentAngle - distanceToTargetAngle) / 180;
    if (error == 0)
        integral = 0;

    integral += error * defaultPeriodInMs;
    derivative = (error - errorPrior) / defaultPeriodInMs;
    double rotation = p*error + i*integral + d*derivative;
    errorPrior = error;
    return rotation;
}

double TurnToAngle::GetRotationMultiplier() {
    double rotMultiplier = 0.75 * pow(3, error);
    return rotMultiplier;
}

double TurnToAngle::LimitMaxTurnSpeed(double currentSpeed) {
    double speed = currentSpeed;
    if (currentSpeed < maxTurnSpeed * -1)
        speed = maxTurnSpeed * -1;
    else if (currentSpeed > maxTurnSpeed)
        speed = maxTurnSpeed;
    return speed;
}

void TurnToAngle::End(bool interrupted) {}

bool TurnToAngle::IsFinished() {
    return std::abs(error) < minError;
}

double TurnToAngle::GetCurrentError() {
    return error;
}

double TurnToAngle::GetMinimumError() {
    return minError;
}