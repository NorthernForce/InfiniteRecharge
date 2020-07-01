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
 }

void AutoCommandScheduler::Run() {
    if (isFinished)
        EndIfGoneThroughAllIndexes();
    else
        ScheduleCommandsInSequence();
}

void AutoCommandScheduler::ScheduleCommandsInSequence() {
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