/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraMount.h"
#include "RobotContainer.h"
#include "Constants.h"

int CameraMount::sweepPassCount;

CameraMount::CameraMount() {
    panServo = std::make_shared<frc::Servo>(Constants::MotorIDs::panServoPWM);
    tiltServo = std::make_shared<frc::Servo>(Constants::MotorIDs::tiltServoPWM);
    Init();
    SetToZero();
}

void CameraMount::Init() {
    currentPan = 90;
    currentTilt = 0;
    previousPan = 90;
    previousTilt = 0;
    // std::thread syncThread(SyncServoAngles);
}

void CameraMount::Periodic() {
    pcOffset = RobotContainer::aiComms->GetPCOffsetInCameraX();
    SetLastNonZeroPcOffset();
    LimitStoredAngles();
    recentPanAngles.push_front(GetCurrentPan());
}

int CameraMount::GetServoAngleToTarget() {
    return servoAngleToTarget;
}

void CameraMount::SmartSweep() {
    int millisSinceTargetRegistered = RobotContainer::aiVisionTargetting->TimeSinceTargetRegisteredInMillis();
    bool isTargetFound = RobotContainer::aiComms->IsTargetFound();

    if (millisSinceTargetRegistered >= 750) {
        hasMovedServoBackToTarget = false;
        if (isTargetFound)
            CenterTarget();
        else
            Sweep();
    }
    else if (!hasMovedServoBackToTarget)
        MoveServoBackToTarget();
}

void CameraMount::Sweep() {
    if (lastNonZeroPcOffset < -6 || sweepPassCount % 2 == 0) {
        Pan(currentPan);
        currentPan++;
    } else if (lastNonZeroPcOffset > 6 || sweepPassCount % 2 == 1) {
        Pan(currentPan);
        currentPan--;
    }
    if (currentPan <= 35 || currentPan >= 155) {
        sweepPassCount++;
        lastNonZeroPcOffset = 0;
    }

    RecoverOutOfRangeServo();
}

void CameraMount::CenterTarget() {
    if (pcOffset < -6)
        Pan(++currentPan);
    else if (pcOffset > 6)
        Pan(--currentPan);
}

void CameraMount::MoveServoBackToTarget() {
    if (lastNonZeroPcOffset < -6)
        currentPan += 6;
    else if (lastNonZeroPcOffset > 6)
        currentPan -= 6;
    Pan(currentPan);
    hasMovedServoBackToTarget = true;
}

void CameraMount::SetToZero() {
    Pan(90);
    Tilt(90);
}

int CameraMount::GetCurrentPan() {
    currentPan = panServo->GetAngle();
    return currentPan;
}

int CameraMount::GetPreviousPan() {
    return previousPan;
}

int CameraMount::GetAvgOfRecentPans() {
    int sum = 0;
    int arrayLen = recentPanAngles.size();
    for (auto ang : recentPanAngles)
        sum += ang;
    return sum / arrayLen;
}

int CameraMount::GetCurrentTilt() {
    currentTilt = tiltServo->GetAngle();
    return currentTilt;
}

int CameraMount::GetPreviousTilt() {
    return previousTilt;
}

void CameraMount::Pan(int degrees) {
    previousPan = currentPan;
    currentPan = degrees;
    panServo->SetAngle(degrees);
}

void CameraMount::Tilt(int degrees) {
    previousTilt = currentTilt;
    currentTilt = degrees;
    tiltServo->SetAngle(degrees);
}

char CameraMount::GetPanDirection() {
    if (currentPan < 90)
        panDirection = 'r';
    else
        panDirection = 'l';
    return panDirection;
}

void CameraMount::RecoverOutOfRangeServo() {
    int angle = panServo->GetAngle();
    if (angle > 155)
        Pan(angle-3);
    else if (angle < 35)
        Pan(angle+3);
}

void CameraMount::SetLastNonZeroPcOffset() {
    if (pcOffset != 0)
        lastNonZeroPcOffset = pcOffset;
}

void CameraMount::LimitStoredAngles() {
    if (recentPanAngles.size() > 50)
        recentPanAngles.pop_back();
}