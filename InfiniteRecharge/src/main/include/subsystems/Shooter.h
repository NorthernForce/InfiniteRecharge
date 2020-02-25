/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();
  void SetFollowers();
  void Shoot();
  void Periodic();
  void ConfigureController(rev::CANSparkMax& controller, double ramp);

 private:
  std::shared_ptr<rev::CANSparkMax> shooterSpark;
  std::shared_ptr<rev::CANPIDController> pidController;

  const double p = 0.5;
  const double i = 0.0;
  const double d = 0.0;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  static double rampRate;

};
