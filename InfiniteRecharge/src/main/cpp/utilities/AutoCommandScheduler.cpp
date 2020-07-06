/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/AutoCommandScheduler.h"

int AutoCommandScheduler::currIndex;

AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> &&commandQueue) {
    this->commandQueue = commandQueue;
    maxIndex = commandQueue.size() - 1;
    doCommandsHaveSharedSubsystems = CheckForSubsystemConflictsInCommandQueue();
}

AutoCommandScheduler::AutoCommandScheduler() {}

void AutoCommandScheduler::RunSequential() {
    if (!isFinished)
        ScheduleInSequence();
}

void AutoCommandScheduler::ScheduleInSequence() {
    int prevInd = GetPrevIndex();
    if (!commandQueue[prevInd]->IsScheduled() && currIndex <= maxIndex) {
        commandQueue[currIndex]->Schedule();
        currIndex++;
    }
    else 
        CheckAllCommandsHaveFinished();
}

int AutoCommandScheduler::GetPrevIndex() {
    int prevInd = 0;
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