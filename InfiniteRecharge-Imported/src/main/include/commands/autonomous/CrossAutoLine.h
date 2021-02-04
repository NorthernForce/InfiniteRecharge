/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "utilities/AutoCommandScheduler.h"

class CrossAutoLine
    : public frc2::CommandHelper<frc2::CommandBase, CrossAutoLine> {
 public:
  CrossAutoLine();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;

 private:
    std::unique_ptr<AutoCommandScheduler> autoCommandScheduler;

};
