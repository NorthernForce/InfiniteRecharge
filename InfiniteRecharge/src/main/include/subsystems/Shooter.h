/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();
  void SetFollowers();
  void ShootCell();
  void Periodic();
  void SetupControllers();
  void ConfigureController(rev::CANSparkMax& controller);

 private:

  std::shared_ptr<rev::CANSparkMax> primary;
  std::shared_ptr<rev::CANSparkMax> follower1;
  std::shared_ptr<rev::CANSparkMax> follower2;
  std::shared_ptr<rev::CANSparkMax> follower3;

  int currentLimit = 60;
  int secondaryCurrentLimit = 80;
  double rampRate = 0.2;

};
