/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"

Shooter::Shooter() {
    primary.reset(new rev::CANSparkMax(Constants::Shooter::primary, rev::CANSparkMax::MotorType::kBrushless));
    follower1.reset(new rev::CANSparkMax(Constants::Shooter::follower1, rev::CANSparkMax::MotorType::kBrushless));
    follower2.reset(new rev::CANSparkMax(Constants::Shooter::follower2, rev::CANSparkMax::MotorType::kBrushless));
    follower3.reset(new rev::CANSparkMax(Constants::Shooter::follower3, rev::CANSparkMax::MotorType::kBrushless));
}

void Shooter::SetFollowers(){
    follower1->Follow(*primary, true);
    follower2->Follow(*primary, true);
    follower3->Follow(*primary, true);
}
void Shooter::ConfigureController(rev::CANSparkMax& controller) {
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  if(!controller.IsFollower())
  {
    controller.SetClosedLoopRampRate(rampRate);
    controller.SetOpenLoopRampRate(rampRate);
  }
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

void Shooter::ShootCell(){
    primary->Set(0.5);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}
