/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"

class Intake : public frc2::SubsystemBase {
 public:
  Intake();
  void Periodic();
  void TakeIn();
  void PushOut();
  void Stop();
  bool ArmUp();
  bool ArmDown();
  bool ArmState();


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  bool armState;

  std::shared_ptr<rev::CANSparkMax> intakeSpark;
  std::shared_ptr<rev::CANSparkMax> armSpark;
};
