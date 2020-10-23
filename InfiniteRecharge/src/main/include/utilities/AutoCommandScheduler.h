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
  void CustomAuto(std::vector<std::string> driverInput, std::vector<double> dashboardParams);
  bool IsFinished();
  std::vector<frc2::Command*> commandQueue;

 private:
    std::vector<double> DashParamToDouble(std::string, unsigned int);
    int GetPrevIndex();
    void ScheduleInSequence();
    void ScheduleInParallel();
    void EndIfGoneThroughAllIndexes();
    bool CheckForSubsystemConflictsInCommandQueue();
    std::vector<frc2::Subsystem*> GetRequiredSubsystems();
    void CheckAllCommandsHaveFinished();
    void CleanUpArray(std::vector<frc2::Command*> array);

    std::vector<double> dashParams;
    static int currIndex;
    int maxIndex;
    bool isFinished = false;
    bool doCommandsHaveSharedSubsystems = false;
    bool parallelScheduledOnce = false;
    bool isUsingAuto = false;
    bool hasScheduledAuto = false;

    struct BaseException : public std::exception {};
    struct CommandConflictError : public BaseException {
        const char * what () const throw () {
            const char *error_message = "CommandConflictError: Commands that require the same subsystems cannot be run in parallel.\n"
            "This is due to an intentional limitation of the WPILib.\n";
            return error_message;
        }
    };

    enum class CommandTypes {
        Drive,
        Turn,
        Intake,
        Shoot,
        AutoBallSeek,
        Coordinate
    };
    std::map<std::string, CommandTypes> stringToCommandTypes = {
        { "Drive", CommandTypes::Drive },
        { "Turn", CommandTypes::Turn },
        { "Intake", CommandTypes::Intake },
        { "Shoot", CommandTypes::Shoot },
        { "AutoBallSeek", CommandTypes::AutoBallSeek },
        {"Coordinate", CommandTypes::Coordinate }
    };
};
