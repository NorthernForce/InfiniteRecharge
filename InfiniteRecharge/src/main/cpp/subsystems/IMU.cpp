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
}

void IMU::Init() {
    ahrs->ResetDisplacement();
}

void IMU::Periodic() {
    double currentAccelX = ahrs->GetWorldLinearAccelX();
    previousAccelX = currentAccelX;

    double currentAccelY = ahrs->GetWorldLinearAccelY();
    previousAccelY = currentAccelY;
}

double IMU::GetRollAngle() {
    return ahrs->GetRoll();
}

double IMU::GetRotation() {
    return ahrs->GetYaw();
}

void IMU::Reset() {
    ahrs->Reset();
}