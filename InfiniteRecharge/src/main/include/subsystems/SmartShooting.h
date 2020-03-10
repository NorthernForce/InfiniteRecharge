/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class SmartShooting : public frc2::SubsystemBase {
 public:
  SmartShooting();
  void Periodic();
  bool ShooterIsOn();
  bool ShooterIsUp();
  double GetDistance();
  void ControlDistance();
  double WantedShooterRPM();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
