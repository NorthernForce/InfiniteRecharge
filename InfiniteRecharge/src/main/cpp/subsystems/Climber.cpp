/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

const int Climber::timeout = 0;
const int Climber::peakCurrent = 35;
const int Climber::continuousCurrent = 25;
const int Climber::peakCurrentDuration = 2000;


Climber::Climber() {
    armTalon = std::make_shared<WPI_TalonSRX>(Constants::MotorIDs::climberArm);
}

// This method will be called once per scheduler run
void Climber::Periodic() {}

void Climber::SetLifter(double speed) {
    armTalon->Set(speed);
}

void Climber::SetCurrentLimits(WPI_TalonSRX& controller) {
    controller.ConfigPeakCurrentLimit(peakCurrent, timeout);
    controller.ConfigContinuousCurrentLimit(continuousCurrent, timeout);
    controller.ConfigPeakCurrentDuration(peakCurrentDuration, timeout);
    controller.EnableCurrentLimit(true);
} 

