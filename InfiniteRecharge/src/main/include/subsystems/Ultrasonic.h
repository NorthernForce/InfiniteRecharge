/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AnalogInput.h>
#include "Constants.h"
//#include <frc/DigitalOutput.h>

//all digital stuff is commented out

class Ultrasonic : public frc2::SubsystemBase {
 public:
  Ultrasonic();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  double GetDistance();
  void Enable();
  void Disable();
  bool IsObstacleAt(int targetDistance);

  double distance;
  bool isObstacleDetected;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  static constexpr double ValueToInches = 0.125;

  bool ultrasonicState;

  std::shared_ptr<frc::AnalogInput> analogUltrasonic;

  //std::shared_ptr<frc::DigitalOutput> ctrl;

  const static bool ultrasonicOn = true;
  const static bool ultrasonicOff = false;
};
