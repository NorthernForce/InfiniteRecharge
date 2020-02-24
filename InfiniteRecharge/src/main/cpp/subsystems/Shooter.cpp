/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"

double Shooter::rampRate;

Shooter::Shooter() {
    primarySpark.reset(new rev::CANSparkMax(Constants::MotorIDs::shooterPrimary, rev::CANSparkMax::MotorType::kBrushless));
    rampRate = 0.2;
    ConfigureSpark();
}

void Shooter::Shoot() {
    primarySpark->Set(0.5);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}

void Shooter::ConfigureSpark(double ramp) {
  auto &controller = *primarySpark;
  rampRate = ramp;
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  if(!controller.IsFollower())
  {
    controller.SetClosedLoopRampRate(ramp);
    controller.SetOpenLoopRampRate(ramp);
  }
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}