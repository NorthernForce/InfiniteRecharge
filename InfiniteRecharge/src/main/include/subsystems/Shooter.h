/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <frc/Timer.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();
  void Periodic();
  void ConfigureSpark(double ramp=rampRate);
  void IdleShooter(); 
  double GetSpeedFromPID(double p, double i, double d);
  void Shoot();
  void SetSpeed(double speed);
  int GetCurrentRPM();
  void SetCurrentRPM(int rpm);
  int GetTargetRPM();
  void SetTargetRPM(int rpm);
  int GetError();
  void ShooterUp();
  void ShooterDown();

  const bool shiftOn = true;
  const bool shiftOff = false;

 private:
  std::shared_ptr<rev::CANSparkMax> shooterSpark;
  std::shared_ptr<rev::CANPIDController> pidController;
  std::shared_ptr<frc::Solenoid> shooterShifter;
  std::shared_ptr<frc::Timer> timer;

  double p = 0.4;
  double i = 0;
  double d = 0.3; 
  double ff = 1.0;
  const int maxI = 100;
  
  double error;
  double integral;
  double derivative;
  double errorPrior;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  static double rampRate;
  int targetRPM = 2200;
  double idlePercentage = 0.6; //units are decimals from 0-1
};
