/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"
#include "RobotContainer.h"


Shooter::Shooter() {
  shooterSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::shooter, rev::CANSparkMax::MotorType::kBrushless));
  pidController.reset(new rev::CANPIDController(shooterSpark->rev::CANSparkMax::GetPIDController()));
  shooterShifter.reset(new frc::Solenoid(Constants::PCMCanBusID, 1));
  timer.reset(new frc::Timer());

  pidController->SetP(p);
  pidController->SetI(i);
  pidController->SetD(d); 
  pidController->SetFF(ff); 
  pidController->SetIMaxAccum(max_i);

  ConfigureSpark(.2);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}

void Shooter::ConfigureSpark(double ramp) {
  auto &controller = *shooterSpark; //nice
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  controller.SetClosedLoopRampRate(rampRate);
  controller.SetOpenLoopRampRate(rampRate);
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void Shooter::IdleShooter() {
  pidController->SetReference(shooterRPM * IdlePercentage / 100, rev::ControlType::kVelocity );
}
void Shooter::Shoot() {
  pidController->SetReference(shooterRPM, rev::ControlType::kVelocity);
}

void Shooter::SetRPM(int rpm) {
  pidController->SetReference(rpm, rev::ControlType::kVelocity);
}
void Shooter::SetSpeed(double speed) {
  shooterSpark->Set(speed);
}

int Shooter::GetRPM() {
  return shooterSpark->GetEncoder().GetVelocity();
}

int Shooter::GetError() {
  return GetRPM() - shooterRPM;
}

void Shooter::AddToShooterRPM(int change) {
  shooterRPM += change;
}

void Shooter::ShooterUp() {
  shooterShifter->Set(shiftOn); 
}

void Shooter::ShooterDown() {
  shooterShifter->Set(shiftOff);
}