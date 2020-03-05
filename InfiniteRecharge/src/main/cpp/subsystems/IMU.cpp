/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IMU.h"
#include <frc/SPI.h>

IMU::IMU() {
    ahrs.reset(new AHRS(SPI::Port::kMXP));
    Init();
    accelerationRateTimer.reset(new frc::Timer());
    accelerationRateTimer->Start();
}

void IMU::Init() {
    ahrs->ResetDisplacement();
    ZeroRotation();
}

void IMU::Periodic() {
    double currentAccelX = ahrs->GetWorldLinearAccelX();
    previousAccelX = currentAccelX;

    double currentAccelY = ahrs->GetWorldLinearAccelY();
    previousAccelY = currentAccelY;

    if (std::abs(currentAccelY - previousAccelY) >= torqueThreshold) {
        accelerationRateTimer->Reset();
        accelerationRateTimer->Start();
    }
    std::cout << "currentrot: " << GetRotation() << "\n";
}

double IMU::GetRollAngle() {
    return ahrs->GetRoll();
}

double IMU::GetRotation() {
    return ahrs->GetYaw();
}

void IMU::ZeroRotation() {
    ahrs->ZeroYaw();
}

void IMU::Reset() {
    ahrs->Reset();
}

double IMU::GetAcceleration() {
    return currentAccelY;
}

bool IMU::IsMoreTorqueNeeded() {
    if (accelerationRateTimer->Get() < 0.1)
        return true;
    else
        return false;
}