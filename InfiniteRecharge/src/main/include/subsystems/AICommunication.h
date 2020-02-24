/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <string>

class AICommunication : public frc2::SubsystemBase {
 public:
  AICommunication();
  std::vector<double> GetValueArray(std::string key);
  double GetNumber(std::string key);
  void Periodic();
  const std::string powercellOffsetInCam =  "PC Offset in AI Cam:";
  const std::string powercellDistanceInCam = "PC Distance in AI Cam:";

 private:
};
