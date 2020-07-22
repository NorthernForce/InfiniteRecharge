/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/AutoCommandScheduler.h"
#include "commands/AutoDrive.h"
#include "commands/TurnToAngle.h"
#include "commands/IntakePowerCell.h"
#include "commands/ShootCell.h"
#include "commands/autonomous/AutoBallSeek.h"
#include "commands/IntakePowerCell.h"
#include <frc/smartdashboard/SmartDashboard.h>

int AutoCommandScheduler::currIndex;

AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> &&commandQueue) {
    this->commandQueue = commandQueue;
    maxIndex = commandQueue.size() - 1;
    doCommandsHaveSharedSubsystems = CheckForSubsystemConflictsInCommandQueue();
}

AutoCommandScheduler::AutoCommandScheduler() {
    isUsingAuto = true;
}

void AutoCommandScheduler::CustomAuto(std::vector<std::string> driverInput, std::vector<std::string> dashboardParams) {

for(int i = 0; i < driverInput.size(); i++) {

    double commandParam;
    std::string dashInput;

    commandParam = dashboardParams[i];
    CommandTypes commandType = stringToCommandTypes[dashInput];
    switch (commandType)
    {
    case CommandTypes::Drive:
        commandQueue.push_back(new AutoDrive(commandParam));
        break;
    
    case CommandTypes::Turn:
        commandQueue.push_back(new TurnToAngle(commandParam));
        break;
    
    case CommandTypes::Intake:
        commandQueue.push_back(new IntakePowerCell());
        break;
    
    case CommandTypes::Shoot:
        commandQueue.push_back(new AutoShootCell());
        break;
    
    case CommandTypes::AutoBallSeek:
        commandQueue.push_back(new AutoBallSeek());
        break;
    
    default:
        break;
    }
}

    if ((driverInput[0] == "Turn") && (driverInput[1] == "GoForward")) {
        commandQueue.push_back(new TurnToAngle(frc::SmartDashboard::GetNumber("auto 1 parameter", 0)));
        commandQueue.push_back(new AutoDrive(frc::SmartDashboard::GetNumber("auto 2 parameter", 0)));
    } else if ((driverInput[0] == "GoForward") && (driverInput[1] == "Turn")) {
        commandQueue.push_back(new AutoDrive(frc::SmartDashboard::GetNumber("auto 1 parameter", 0)));
        commandQueue.push_back(new TurnToAngle(frc::SmartDashboard::GetNumber("auto 2 parameter", 0)));
    }
    maxIndex = commandQueue.size() - 1;
    hasScheduledAuto = true;
}

void AutoCommandScheduler::RunSequential() {
    if (isFinished)
        EndIfGoneThroughAllIndexes();
    else if (isUsingAuto == false or (isUsingAuto == true and hasScheduledAuto == true))
        ScheduleInSequence();
}

void AutoCommandScheduler::ScheduleInSequence() {
    int prevInd = GetPrevIndex();
    if (!commandQueue[prevInd]->IsScheduled() && currIndex <= maxIndex) {
        commandQueue[currIndex]->Schedule();
        currIndex++;
    }
}

int AutoCommandScheduler::GetPrevIndex() {
    int prevInd=0;
    if (currIndex > 0)
        prevInd = currIndex-1;
    return prevInd;
}

void AutoCommandScheduler::RunParallel() {
    if (!isFinished)
        ScheduleInParallel();
}

void AutoCommandScheduler::ScheduleInParallel() {
    if (!doCommandsHaveSharedSubsystems) {
        if (currIndex <= maxIndex) {
            commandQueue[currIndex]->Schedule();
            currIndex++;
        }
        else
            CheckAllCommandsHaveFinished();
    }
    else
        throw CommandConflictError();
}

bool AutoCommandScheduler::CheckForSubsystemConflictsInCommandQueue() {
    for (int currInd = 0; currInd < maxIndex; currInd++) {
        double nextInd = currInd + 1;
        if (commandQueue[currInd] == commandQueue[nextInd]) {
            commandQueue.erase(commandQueue.begin() + currInd);
            currInd--;
        }
    }
    return false;
}

std::vector<frc2::Subsystem*> AutoCommandScheduler::GetRequiredSubsystems() {
    std::vector<frc2::Subsystem*> requirements;

    for (auto cmd : commandQueue) {
        for (auto requirement : cmd->GetRequirements())
        requirements.push_back(requirement);
    }
    return requirements;
}

void AutoCommandScheduler::CheckAllCommandsHaveFinished() {
    if (!commandQueue[maxIndex]->IsScheduled())
        isFinished = true;
}

bool AutoCommandScheduler::IsFinished() {
    return isFinished;
}

void AutoCommandScheduler::EndIfGoneThroughAllIndexes() {
    if (currIndex >= maxIndex) {
        currIndex = 0;
        isFinished = true;
    }
    CleanUpArray(commandQueue);
}

void AutoCommandScheduler::CleanUpArray(std::vector<frc2::Command*> array) {
    for (auto elem : array)
        delete elem;
}