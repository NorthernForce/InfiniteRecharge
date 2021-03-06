/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

class Limelight : public frc2::SubsystemBase {
 public:
  Limelight();
  double GetXOffset();
  bool IsTargetThere();
  double GetTargetArea();
  double GetTargetSkew();
  void PutNumberToTable(std::string key, double number);
  double GetNumberFromTable(std::string key, double defaultValue=0);
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");


  void Periodic();

 private:

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
