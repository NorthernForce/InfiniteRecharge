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
  void IdleShooter();
  void Shoot();
  void Periodic();
  void ConfigureSpark(double ramp);  
  void SetSpeed(double speed);
  int GetRPM();
  void SetRPM(int rpm);
  int GetError();
  void AddToShooterRPM(int change);
  void ShooterUp();
  void ShooterDown();
  void TuneRpmPid_P();
  void ShootByDist();

  const bool shiftOn = true;
  const bool shiftOff = false;

 private:
  std::shared_ptr<rev::CANSparkMax> shooterSpark;
  std::shared_ptr<rev::CANPIDController> pidController;
  std::shared_ptr<frc::Solenoid> shooterShifter;
  std::shared_ptr<frc::Timer> timer;

  const double p = 1.6 * 0.8;
  const double i = 0;
  const double max_i = 100;
  const double d = 0; 
  const double ff = 0; 
  
  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  double rampRate = 0;
  int shooterRPM = 2200;
  double IdlePercentage = 60; //units of this are %
};
