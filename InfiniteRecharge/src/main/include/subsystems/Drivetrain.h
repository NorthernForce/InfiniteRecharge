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
  void RecordMotorPos();
  void SetInvertedFollowers();
  void ConfigureAllControllers();
  void Drive(double speed, double rotation);
  void DriveUsingSpeeds(double leftSpeed, double rightSpeed);
  void Periodic();
  void ConfigureController(rev::CANSparkMax& controller);
  double GetRightRPM();
  double GetLeftRPM();
  double GetAvgRPM();
  std::pair<double, double> GetEncoderRotations();
  double GetAvgEncoderRotations();
  void SimpleDriveWithEncoder(double desiredEncoder);
  void SetEncoderPosition(double position);
  int GetSpeedInInchesPerSecond();
  void WriteLeftMotorPos(std::string fileName);
  void WriteRightMotorPos(std::string fileName);
  void PlayRecordedRun(std::vector<double> leftMotorVals, std::vector<double> rightMotorVals);
  std::vector<double> GetMotorVals(char side);

  static std::shared_ptr<rev::CANSparkMax> leftPrimarySpark;
  static std::shared_ptr<rev::CANSparkMax> rightPrimarySpark;
  static std::shared_ptr<frc::DifferentialDrive> robotDrive;

  std::vector<double> leftMotorPos;
  std::vector<double> rightMotorPos;

  bool continueDrive;
  bool hasDriven;
  int currentEncoder;
  int prevEncoder;
  const int loopCyclesInOneSecond = 50;


 private:
  void setPID();
  
  std::shared_ptr<rev::CANSparkMax> leftFollowerSpark1;
  std::shared_ptr<rev::CANSparkMax> leftFollowerSpark2;

  std::shared_ptr<rev::CANSparkMax> rightFollowerSpark1;
  std::shared_ptr<rev::CANSparkMax> rightFollowerSpark2;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  double rampRate = 0.2;

  //////////////////////////////////////////////////////
  std::shared_ptr<rev::CANPIDController> leftPID;
  std::shared_ptr<rev::CANPIDController> rightPID;

  double kP = 0.3;
  double kI;
  double kD;
  double kFF = 0.25;
  double kIz;
  double kMinOutput = -1;
  double kMaxOutput = 1;


};
