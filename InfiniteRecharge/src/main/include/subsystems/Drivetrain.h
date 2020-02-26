/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();
  void SetInvertedFollowers();
  void ConfigureAllControllers();
  void Drive(double speed, double rotation);
  void Periodic();
  void ConfigureController(rev::CANSparkMax& controller);
  double GetRightRPM();
  double GetLeftRPM();
  std::pair<double, double> GetEncoderRotations();
  void SetEncoderPosition(double position);
  void DriveInInches(double inches, double leftSpeed=0.75, double rightSpeed=0.75);

  static std::shared_ptr<rev::CANSparkMax> leftPrimarySpark;
  static std::shared_ptr<rev::CANSparkMax> rightPrimarySpark;

  static std::shared_ptr<frc::DifferentialDrive> robotDrive;

 private:
  std::shared_ptr<rev::CANSparkMax> leftFollowerSpark1;
  std::shared_ptr<rev::CANSparkMax> leftFollowerSpark2;

  std::shared_ptr<rev::CANSparkMax> rightFollowerSpark1;
  std::shared_ptr<rev::CANSparkMax> rightFollowerSpark2;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  double rampRate = 0.2;
};
