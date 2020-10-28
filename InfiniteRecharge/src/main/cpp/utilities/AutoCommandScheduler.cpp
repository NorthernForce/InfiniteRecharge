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
#include "commands/autonomous/MoveToCoordinate.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <math.h>

int AutoCommandScheduler::currIndex;


AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> &&commandQueue) {
    this->commandQueue = commandQueue;
    maxIndex = commandQueue.size() - 1;
    doCommandsHaveSharedSubsystems = CheckForSubsystemConflictsInCommandQueue();
}

AutoCommandScheduler::AutoCommandScheduler() {
    isUsingAuto = true;
}

std::vector<double> AutoCommandScheduler::StringSplitter(std::string input, std::string delim) {
    std::vector<double> tokens;

    size_t pos = 0;
    while ((pos = input.find(delim)) != std::string::npos) {
        tokens.push_back(std::stod(input.substr(0, pos)));
        input.erase(0, pos + delim.length());
    }
    tokens.push_back(std::stod(input.substr(0, pos)));
    return tokens;
}

void AutoCommandScheduler::RunSequential() {
    if (isFinished)
        EndIfGoneThroughAllIndexes();
    else if (!isUsingAuto || (isUsingAuto && hasScheduledAuto))
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
        std::cerr << CommandConflictError().what() << '\n';
}

void AutoCommandScheduler::DashboardAuto(std::vector<std::string> &&driverInput, std::vector<std::string> &&dashboardParams) {
    std::vector<double> cmdParams;

    for (unsigned i = 0; i < driverInput.size(); i++) {
        std::string dashInput = driverInput[i];
        CommandTypes commandType = stringToCommandTypes[dashInput];

        if (commandTypeRequiresParams[commandType])
            cmdParams = StringSplitter(dashboardParams[i+paramIndexCorrector]);
        else
            paramIndexCorrector--;

        switch (commandType) {
            case CommandTypes::Drive:
            //send dashboard param to parser here, already have i value then reintroduce in push back
                commandQueue.push_back(new AutoDrive(cmdParams[0], cmdParams[1], cmdParams[2]));
                break;
            
            case CommandTypes::Turn:
                commandQueue.push_back(new TurnToAngle(cmdParams[0]));
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
            
            case CommandTypes::Coordinate:
                commandQueue.push_back(new MoveToCoordinate(cmdParams[0], cmdParams[1], cmdParams[2]));
                break;
            
            default:
                break;
        }
    }

    maxIndex = driverInput.size() - 1;
    hasScheduledAuto = true;
}

bool AutoCommandScheduler::CheckForSubsystemConflictsInCommandQueue() {
    for (int currInd = 0; currInd < maxIndex; currInd++) {
        double nextInd = currInd + 1;
        if (commandQueue[currInd] == commandQueue[nextInd])
            return true;
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