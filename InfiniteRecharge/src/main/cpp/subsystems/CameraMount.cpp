/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraMount.h"
#include "Constants.h"
#include <chrono>
#include <thread>

int CameraMount::sweepPassCount;
int CameraMount::sweepDegree;

CameraMount::CameraMount() {
    panServo.reset(new frc::Servo(Constants::Servo::panServo));
    tiltServo.reset(new frc::Servo(Constants::Servo::tiltServo));
    Init();
    SetToZero();
    
}

void CameraMount::Init() {
    currentPan = 90;
    currentTilt = 90;
    previousPan = 90;
    previousTilt = 90;
    panDirection = 90;
    tiltDirection = 90;
    sweepDegree = 0;
}

void CameraMount::Pan(int degrees) {
    previousPan = currentPan;
    currentPan = degrees;
    panServo->SetAngle(degrees);
}

int CameraMount::GetCurrentPan() {
    currentPan = panServo->GetAngle();
    return currentPan;
}

int CameraMount::GetPreviousPan() {
    return previousPan;
}

void CameraMount::Tilt(int degrees) {
    previousTilt = currentTilt;
    currentTilt = degrees;
    tiltServo->SetAngle(degrees);
}

int CameraMount::GetCurrentTilt() {
    currentTilt = tiltServo->GetAngle();
    return currentTilt;
}

int CameraMount::GetPreviousTilt() {
    return previousTilt;
}

void CameraMount::SetToZero() {
    Pan(90);
    Tilt(90);
}

void CameraMount::SetAngles(int panAngle, int tiltAngle) {
    Pan(panAngle);
    Tilt(tiltAngle);
}

void CameraMount::IntervaledExecution(std::function<void()> periodicFunction, unsigned msInterval) {
    std::thread([periodicFunction, msInterval]() {
        while (true) { 
            auto timePoint = std::chrono::steady_clock::now() + std::chrono::milliseconds(msInterval);
            periodicFunction();
            std::this_thread::sleep_until(timePoint);
        }
    }).detach();
}

#include "RobotContainer.h"

void CameraMount::SweepForPowercells() {
    RobotContainer::cameraMount->Tilt(90);

    if (sweepPassCount % 2 == 0) {
        if (sweepDegree <= 180) {
            RobotContainer::cameraMount->Pan(sweepDegree);
            sweepDegree++;
        }
    } else if (sweepPassCount % 2 == 1) {
        if (sweepDegree <= 180) {
            RobotContainer::cameraMount->Pan(sweepDegree);
            sweepDegree--;
        }
    }
    if (sweepDegree == 0 || sweepDegree == 180)
        sweepPassCount++;
}

int CameraMount::GetServoAngleToTarget() {
    return servoAngleToTarget;
}


// This method will be called once per scheduler run
void CameraMount::Periodic() {}