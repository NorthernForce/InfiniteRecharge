/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "RobotContainer.h"
#include "subsystems/DriveShifter.h"

class ShiftGear
    : public frc2::CommandHelper<frc2::CommandBase, ShiftGear> {
 public:
  using Gear = DriveShifter::Gear;
  ShiftGear(Gear gear);
  void Initialize() override;
  bool IsFinished() override;

 private:
  Gear m_gear;
  char logMessage[32];
};
