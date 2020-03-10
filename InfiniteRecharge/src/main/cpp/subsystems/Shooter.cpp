/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"
#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>

double Shooter::rampRate;

Shooter::Shooter() {
  shooterSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::shooter, rev::CANSparkMax::MotorType::kBrushless));
  pidController.reset(new rev::CANPIDController(shooterSpark->rev::CANSparkMax::GetPIDController()));
  shooterShifter.reset(new frc::Solenoid(Constants::PCMCanBusID, 1));
  timer.reset(new frc::Timer());

  pidController->SetP(p);
  pidController->SetI(i);
  pidController->SetD(d);
  pidController->SetFF(ff); 
  pidController->SetIMaxAccum(maxI);

  ConfigureSpark(.2);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
  targetRPM = frc::SmartDashboard::GetNumber("Shooter target RPM: ", targetRPM);
}

void Shooter::ConfigureSpark(double ramp) {
  auto &controller = *shooterSpark; //nice
  rampRate = ramp;
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  controller.SetClosedLoopRampRate(rampRate);
  controller.SetOpenLoopRampRate(rampRate);
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void Shooter::IdleShooter() {
  pidController->SetReference(targetRPM * idlePercentage / 100, rev::ControlType::kVelocity );
}

double Shooter::GetSpeedFromPID(double p, double i, double d) {
  // error = 0.8;
  error = GetError();

  integral += error * 20;
  derivative = (error - errorPrior) / 20;
  double speed = p*error + i*integral + d*derivative;
  errorPrior = error;
  return speed;
}

void Shooter::Shoot() {
  // shooterSpark->Set(GetSpeedFromPID(p, i, d));
  pidController->SetReference(targetRPM, rev::ControlType::kVelocity);
}

void Shooter::SetSpeed(double speed) {
  shooterSpark->Set(speed);
}

int Shooter::GetCurrentRPM() {
  return shooterSpark->GetEncoder().GetVelocity();
}

void Shooter::SetCurrentRPM(int rpm) {
  pidController->SetReference(rpm, rev::ControlType::kVelocity);
}

int Shooter::GetTargetRPM() {
  return targetRPM;
}

void Shooter::SetTargetRPM(int rpm) {
  targetRPM = rpm;
}

int Shooter::GetError() {
  return GetCurrentRPM() - targetRPM;
}

void Shooter::ShooterUp() {
  shooterShifter->Set(shiftOn); 
}

void Shooter::ShooterDown() {
  shooterShifter->Set(shiftOff);
}