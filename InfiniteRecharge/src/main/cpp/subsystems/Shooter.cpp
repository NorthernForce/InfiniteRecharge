/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"
#include "RobotContainer.h"

double Shooter::rampRate;

Shooter::Shooter() {
  shooterSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::shooter, rev::CANSparkMax::MotorType::kBrushless));
  pidController.reset(new rev::CANPIDController(shooterSpark->rev::CANSparkMax::GetPIDController()));
  shooterShifter.reset(new frc::Solenoid(Constants::PCMCanBusID, 1));
  timer.reset(new frc::Timer());

  pidController->SetP(p);
  pidController->SetI(i);
  pidController->SetD(d); 

  ConfigureSpark(.2);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}

void Shooter::ConfigureSpark(double ramp) {
  auto &controller = *shooterSpark;
  rampRate = ramp;
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  controller.SetClosedLoopRampRate(ramp);
  controller.SetOpenLoopRampRate(ramp);
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
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
  shooterSpark->Set(GetSpeedFromPID(p, i, d));
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

double Shooter::RpmPidLoop(double targetRpm) {
  rpmError = targetRpm - GetRPM();
  rpmP = targetRpm / 2500;

  if(rpmError < targetRpm * 0.5)
    rpmIntegral += rpmError;
  
  if(rpmI > 1000)
    rpmIntegral = 500;
  
  rpmDerivative = rpmErrorPrior - rpmError;

  double speed = (rpmP * rpmError + rpmI * rpmIntegral + rpmD * rpmDerivative)/5000;
  if (speed > 1.0)
    speed = 1.0;

  return speed;
}

void Shooter::TuneRpmPid_P() {
  double originP = rpmP;
  double accuracy = 1;
  for (int i=0; i < 10; i++) {
    timer->Stop();
    timer->Reset();
    timer->Start();
    while ((timer->Get() < 6) && (error > 0))
      RpmPidLoop(1000);

    if (timer->Get() >= 6)
      i = 10;
    else if (error > 10)
      rpmP += originP * pow(2, -accuracy) ;
    else if (error < -10)
      rpmP -= originP * pow(2,-accuracy);

    shooterSpark->Set(0.0);

    while(GetRPM() > 50) {}

    accuracy++;
  }
  
  std::cout << rpmP;
}