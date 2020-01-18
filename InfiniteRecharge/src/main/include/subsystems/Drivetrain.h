/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/Drive/DifferentialDrive.h>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();
  void SetFollowers();
  void SetRamp();
  void InvertFollowers();
  void Drive(double speed, double rotation);
  void Periodic();

 private:
  std::shared_ptr<rev::CANSparkMax> leftPrimarySpark;
  std::shared_ptr<rev::CANSparkMax> leftFollowerSpark1;
  std::shared_ptr<rev::CANSparkMax> leftFollowerSpark2;

  std::shared_ptr<rev::CANSparkMax> rightPrimarySpark;
  std::shared_ptr<rev::CANSparkMax> rightFollowerSpark1;
  std::shared_ptr<rev::CANSparkMax> rightFollowerSpark2;

  std::shared_ptr<frc::DifferentialDrive> robotDrive;
};
