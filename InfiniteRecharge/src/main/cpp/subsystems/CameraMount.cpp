/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraMount.h"
#include "RobotContainer.h"
#include "Constants.h"
#include <unistd.h>
#include <thread>

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

void CameraMount::Periodic() {}

void CameraMount::SyncServoAngles() {
    currentPan = panServo->GetAngle();
    currentTilt = panServo->GetAngle();
    sleep(20);
}

int CameraMount::GetServoAngleToTarget() {
    return servoAngleToTarget;
}

void CameraMount::Sweep() {
    std::cout << "sweep\n";
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

    RecoverOutOfRangeServo();
}

void CameraMount::SmartSweep() {
    auto pcOffset = RobotContainer::aiComms->GetCamTargetOffsets(powercell)[0];
    if (RobotContainer::aiComms->IsTargetFound()) {
        if (pcOffset < -6)
            RobotContainer::cameraMount->Pan(round(currentPan+=0.5));
        else if (pcOffset > 6)
            RobotContainer::cameraMount->Pan(round(currentPan-=0.5));
    }
    else
        Sweep();

    if (RobotContainer::aiVisionTargetting->IsTargetCentered())
        RobotContainer::cameraMount->Pan(currentPan);
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
        panDirection = 'r';
    else
        panDirection = 'l';
    return panDirection;
}

void CameraMount::RecoverOutOfRangeServo() {
    int angle = panServo->GetAngle();
    if (angle > 155)
        Pan(--angle);
    else if (angle < 35)
        Pan(++angle);
}