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
#include <frc/DigitalInput.h>

class Intake : public frc2::SubsystemBase {
 public:
  Intake();
  void Periodic();
  void SetFollowers();
 
  void TakeIn();
  void PushOut();
  void Stop();
  bool ArmUp();
  bool ArmDown();
  bool ArmState();

  void RunConveyor();
  void StopConveyor();


  ////TODO: add ramp rate?


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  bool armState;

  std::shared_ptr<frc::DigitalInput> ballPosition1;
  std::shared_ptr<frc::DigitalInput> ballPosition2;
  std::shared_ptr<frc::DigitalInput> ballPosition3;
  std::shared_ptr<frc::DigitalInput> ballPosition4;
  std::shared_ptr<frc::DigitalInput> ballPosition5;


  std::shared_ptr<rev::CANSparkMax> intakeSpark;
  std::shared_ptr<rev::CANSparkMax> armSpark;

  std::shared_ptr<rev::CANSparkMax> primaryConveyorSpark;
  std::shared_ptr<rev::CANSparkMax> followerConveyorSpark;
};
