/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Solenoid.h>
#include <rev/CANSparkMax.h>

class DriveShifter : public frc2::SubsystemBase {
 public:
  enum class Gear {
    Low,
    High
  };
  DriveShifter();
  void Periodic();
  
  void Shift(Gear gear);
  void CheckVelocityForShift(int leftSpeedInRPM, int rightSpeedInRPM);
  Gear GetGear();
  bool IsShiftDone() const;
  void BeginShift(bool shift);

 private:
  std::shared_ptr<frc::Solenoid> shifter;
  Gear currentGear;
  std::shared_ptr<rev::CANSparkMax> leftSideSpark;
  std::shared_ptr<rev::CANSparkMax> rightSideSpark;
  mutable int shiftCountdown;
  const int velocityForShift = 1000;
};
