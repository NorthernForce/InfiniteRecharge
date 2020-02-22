/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"

Shooter::Shooter() {
    primarySpark.reset(new rev::CANSparkMax(Constants::MotorIDs::shooterPrimary, rev::CANSparkMax::MotorType::kBrushless));
    followerSpark1.reset(new rev::CANSparkMax(Constants::MotorIDs::shooterFollower1, rev::CANSparkMax::MotorType::kBrushless));
    followerSpark2.reset(new rev::CANSparkMax(Constants::MotorIDs::shooterFollower2, rev::CANSparkMax::MotorType::kBrushless));
    followerSpark3.reset(new rev::CANSparkMax(Constants::MotorIDs::shooterFollower3, rev::CANSparkMax::MotorType::kBrushless));
}

void Shooter::SetFollowers(){
    followerSpark1->Follow(*primarySpark);
    followerSpark2->Follow(*primarySpark);
    followerSpark3->Follow(*primarySpark);
}

void Shooter::ConfigureController(rev::CANSparkMax& controller, double ramp) {
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  if(!controller.IsFollower())
  {
    controller.SetClosedLoopRampRate(ramp);
    controller.SetOpenLoopRampRate(ramp);
  }
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

void Shooter::Shoot() {
    primarySpark->Set(0.5);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}
