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
  AutoCommandScheduler(std::vector<frc2::Command*> &&commandQueue);
  void Run();
  bool IsFinished();

 private:
    int GetPrevIndex();
    void ScheduleCommandsInSequence();
    void EndIfGoneThroughAllIndexes();
    void CleanUpArray(std::vector<frc2::Command*> array);

    std::vector<frc2::Command*> commandQueue;
    static int currIndex;
    int maxIndex;
    bool isFinished = false;
};
