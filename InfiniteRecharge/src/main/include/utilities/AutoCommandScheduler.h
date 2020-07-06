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
  AutoCommandScheduler();
  void RunSequential();
  void RunParallel();
  bool IsFinished();

 private:
    int GetPrevIndex();
    void ScheduleInSequence();
    void ScheduleInParallel();
    void EndIfGoneThroughAllIndexes();
    bool CheckForSubsystemConflictsInCommandQueue();
    std::vector<frc2::Subsystem*> GetRequiredSubsystems();
    void CheckAllCommandsHaveFinished();

    std::vector<frc2::Command*> commandQueue;
    static int currIndex;
    int maxIndex;
    bool isFinished = false;
    bool doCommandsHaveSharedSubsystems = false;
    bool parallelScheduledOnce = false;

    struct BaseException : public std::exception {};
    struct CommandConflictError : public BaseException {
        const char * what () const throw () {
            const char *error_message = "CommandConflictError: Commands that require the same subsystems can not be run in parallel.\n"
            "This is due to an intentional limitation of the WPILib.\n";
            return error_message;
        }
    };
};
