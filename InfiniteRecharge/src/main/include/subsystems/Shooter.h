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
  void Shoot();
  void Periodic();
  void ConfigureSpark(double ramp=rampRate);  
  double GetSpeedFromPID(double p, double i, double d);
  void SetSpeed(double speed);
  int GetRPM();
  int GetError();
  void AddToShooterRPM(int change);
  void ShooterUp();
  void ShooterDown();
  double RpmPidLoop(double targetRPM);
  void TuneRpmPid_P();
  void ShootByDist();

  const bool shiftOn = true;
  const bool shiftOff = false;

 private:
  std::shared_ptr<rev::CANSparkMax> shooterSpark;
  std::shared_ptr<rev::CANPIDController> pidController;
  std::shared_ptr<frc::Solenoid> shooterShifter;
  std::shared_ptr<frc::Timer> timer;

  const double p = 1.3;
  double rpmP = 1.3;
  const double i = 0.0;
  double rpmI = 0;
  const double d = 0.0; 
  double rpmD = 0;
  
  double error;
  double rpmError;
  double integral;
  double rpmIntegral;
  double derivative;
  double rpmDerivative;
  double errorPrior;
  double rpmErrorPrior;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  static double rampRate;
  int shooterRPM;
};
