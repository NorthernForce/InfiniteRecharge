/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "subsystems/AIVisionTargetting.h"
#include <string>

using Target = AIVisionTargetting::Target;

class AICommunication : public frc2::SubsystemBase {
 public:
  AICommunication();
  void Periodic();
  bool IsTargetFound();
  Target GetTargetType();
  std::vector<double> GetCamTargetOffsets(Target targetType);
  std::vector<double> GetValueArray(std::string key);
  double GetNumber(std::string key);
  double GetPCOffsetInCameraX();
  double GetDistanceToTarget();
  const std::string pcOffsetInCam_label =  "PC Offset in AI Cam: ";
  const std::string distanceToPcFromCam_label = "Distance to PC from Cam:";
  void SwitchCameraToIntake();
  void SwitchCameraToGimbal();

 private:
  AIVisionTargetting::Target powercell = AIVisionTargetting::Target::Powercell;
};