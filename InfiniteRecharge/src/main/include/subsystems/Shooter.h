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
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();
  void Periodic();
  bool GetLazySusanLimitSwitch();
  bool GetHoodLimitSwitch();
  void ConfigureShooterTalon(double ramp=rampRate);
  void IdleShooter(); 
  double GetSpeedFromPID(double p, double i, double d);
  void Shoot();
  void SetRawSpeed(double speed);
  void SetHoodSpeed(double speed);
  int GetCurrentRPM();
  void SetCurrentRPMTo(int rpm);
  int GetTargetRPM();
  void SetTargetRPM(int rpm);
  int GetError();
  void ShooterUp();
  void ShooterDown();
  void SetSusanSpeed(double speed);
  void UpdateLazySusanAngle();
  double GetLazySusanAngle();  
  void CalibrateHood();
  bool IsSusanSpeedWithinLimits(double speed);
  double GetHoodAngle();

  const bool shiftOn = true;
  const bool shiftOff = false;

 private:
  std::unique_ptr<WPI_TalonFX> shooterTalon;
  std::unique_ptr<rev::CANSparkMax> hoodSpark;
  std::unique_ptr<rev::CANSparkMax> susanSpark;
  std::unique_ptr<rev::CANPIDController> pidController;
  std::unique_ptr<frc::Solenoid> shooterShifter;
  std::unique_ptr<frc::Timer> timer;

  double p = 0.4;
  double i = 0;
  double d = 0.3; 
  double ff = 1.0;
  const int maxI = 100;
  const double maxOutput = 1;
  const double minOutput = -1;
  
  double error;
  double integral;
  double derivative;
  double errorPrior;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  static double rampRate;
  int targetRPM = 2200;
  double idlePercentage = 0.6; //units are decimals from 0-1
  int cpr = 2048; // encoder count per rotations
  int msTorpm = 600;

  std::unique_ptr<frc::DigitalInput> hoodLimitSwitch;
  std::unique_ptr<frc::DigitalInput> sexyLimitSwitch;
  double lazySusanAngle;
  const double limitSwitchAngOffset = 0; ////TODO: update this value
};