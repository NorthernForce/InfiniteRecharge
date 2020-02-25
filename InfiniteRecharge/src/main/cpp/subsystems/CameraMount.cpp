/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraMount.h"
#include "RobotContainer.h"
#include "Constants.h"
#include <chrono>
#include <thread>

int CameraMount::sweepPassCount;

CameraMount::CameraMount() {
    panServo.reset(new frc::Servo(Constants::MotorIDs::panServoPWM));
    tiltServo.reset(new frc::Servo(Constants::MotorIDs::tiltServoPWM));
    Init();
    SetToZero();
}

void CameraMount::Init() {
    currentPan = 90;
    currentTilt = 0;
    previousPan = 90;
    previousTilt = 0;
}

void CameraMount::Periodic() {}

int CameraMount::GetServoAngleToTarget() {
    return servoAngleToTarget;
}

void CameraMount::SweepForPowercells() {    
    if (sweepPassCount % 2 == 0) {
        if (currentPan <= 155) {
            Pan(currentPan);
            currentPan++;
        }
    } else if (sweepPassCount % 2 == 1) {
        if (currentPan <= 155) {
            Pan(currentPan);
            currentPan--;
        }
    }
    if (currentPan == 35 || currentPan == 155)
        sweepPassCount++;
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
        panDirection = 'l';
    else
        panDirection = 'r';
    return panDirection;
}