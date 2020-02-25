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
  shooterSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::shooter, rev::CANSparkMax::MotorType::kBrushless));
  pidController.reset(new rev::CANPIDController(shooterSpark->rev::CANSparkMax::GetPIDController()));

  pidController->SetP(p);
  pidController->SetI(i);
  pidController->SetD(d);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}

void Shooter::ConfigureSpark(double ramp) {
  auto &controller = *shooterSpark;
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

void Shooter::Shoot() {
  //  shooterSpark->Set(0.5);
  pidController->SetReference(0.75, rev::ControlType::kVelocity); //code to try and use the pid loop, might be wrong
}
