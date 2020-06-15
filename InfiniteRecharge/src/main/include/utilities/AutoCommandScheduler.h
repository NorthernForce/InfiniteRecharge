/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "RobotContainer.h"
#include <frc2/command/Command.h>
#include <vector>

class AutoCommandScheduler {
 public:
  AutoCommandScheduler(std::vector<frc2::Command*> commandQueue);
  static void ScheduleCmdIfPrevIsFinished(frc2::Command* command, frc2::Command* command_prev);
//   bool IsFinished();

 private:
    // void ScheduleFirstCommand(std::vector<frc2::Command*> cmdList);
    // void AssignVacantPtrs(std::vector<frc2::Command*> cmdList, int indexer, int max);
    // void CleanPtrs();

    // std::vector<frc2::Command*> commandList;
    // bool isFinished;
    int indexer;
};
