/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/ColorSensorV3.h"
#include <rev/CANSparkMax.h>
#include <rev/ColorMatch.h>
#include <frc/util/color.h>
#include "subsystems/utilities/FMSWheelInterface.h"
#include <ctre/Phoenix.h>

// #include <frc/DigitalInput.h>

class WackyWheel : public frc2::SubsystemBase {
 public:
  WackyWheel();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void FindColor();
  void AddColorMatches();
  void MoveToColor();

 private:

  const frc::Color blueTarget = frc::Color(0.143, 0.427, 0.429);
  const frc::Color greenTarget = frc::Color(0.197, 0.561, 0.240);
  const frc::Color redTarget = frc::Color(0.561, 0.232, 0.114);
  const frc::Color yellowTarget = frc::Color(0.361, 0.524, 0.113);

   std::shared_ptr<WPI_TalonSRX> spinnerTalon;
  std::shared_ptr<rev::ColorMatch> colorMatcher;
  std::shared_ptr<FMSWheelInterface> getDesiredColor;
  frc::Color matchedColor;
  frc::Color detectedColor;
  std::shared_ptr<rev::ColorSensorV3> colorSensor;
 
  char colorChar;
  char desiredColor;
  double confidence;
  // std::shared_ptr<frc::DigitalOutput> DigitalColorSensor;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private a nd exposed only through public methods.
};
