/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class AutoDrive
    : public frc2::CommandHelper<frc2::CommandBase, AutoDrive> {
 public:
  AutoDrive(double inches=0, double leftSpeed=0.1, double rightSpeed=0.1);
  void SetDist(double inches);
  double GetDist();
  void SetSpeeds(double leftSpeed=0.3, double rightSpeed=0.3);
  void Initialize() override;
  void CheckForAndFixNegatives();
  void Execute() override;
  void End(bool interrupted) override;
  bool HasReachedTargetDistance();
  bool HasDriveFailed();
  bool IsFinished() override;

 private:
  double inchesToTravel;
  double leftMotorSpeed;
  double rightMotorSpeed;
  double encoderToTravelTo;
  double encoderTravelled;
  double encoderCurrent;
  double startDist;
  bool hasDriven = false;
};
