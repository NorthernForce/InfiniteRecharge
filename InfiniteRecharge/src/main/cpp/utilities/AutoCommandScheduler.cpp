/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/AutoCommandScheduler.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <thread>

// AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> cmdList) {
//     int listLen = cmdList.size() - 1;
//     // ScheduleFirstCommand(cmdList);
//     cmdList[0]->Schedule();

//     for (int i = 0; i <= listLen; i++) { 
//         // AssignVacantPtrs(cmdList, i, listLen);       
//         if ((cmdList[i]->IsFinished()) && (i < listLen)) {
//             cmdList[i+1]->Schedule();
//         }
//         else if ((i >= listLen) || (cmdList[listLen]->IsFinished())) {
//             break;
//         }
//         else {
//             i -= 1; // try again
//         }
//     }
//     isFinished = true;
// }

// AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> commandQueue) {
//     for (auto cmd : commandQueue)
//         cmd->Schedule(false);
// }

// AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> commandQueue) {
//     frc2::Command* cmd_prev = nullptr;
//     for (auto cmd : commandQueue) {
//         if (cmd_prev == nullptr)
//             cmd->Schedule();
//         else
//             ScheduleCmdIfPrevIsFinished(cmd, cmd_prev);
//         cmd_prev = cmd;
//     }
// }

// void AutoCommandScheduler::ScheduleCmdIfPrevIsFinished(frc2::Command* command, frc2::Command* command_prev) {
//     if (!command_prev->IsScheduled())
//         command->Schedule();
//     else
//         ScheduleCmdIfPrevIsFinished(command, command_prev);
// }

AutoCommandScheduler::AutoCommandScheduler(std::vector<std::shared_ptr<frc2::Command>> commandQueue) {
    int maxIndex = commandQueue.size() - 1;

    commandQueue[0]->Schedule();

    for (indexer=1; indexer <= maxIndex; indexer++) {
        frc::SmartDashboard::PutNumber("previous command running?", commandQueue[indexer-1]->IsScheduled());
        if (!commandQueue[indexer-1]->IsScheduled())
            commandQueue[indexer]->Schedule();
        else
            indexer--;
        frc::SmartDashboard::PutNumber("current indexer:", indexer);
    }
}

// AutoCommandScheduler::AutoCommandScheduler(std::vector<frc2::Command*> commandQueue) {
    
//     int maxIndex = commandQueue.size() - 1;
//     commandQueue[0]->Schedule();

//     for (indexer=1; indexer <= maxIndex; indexer++) {
//         frc::SmartDashboard::PutNumber("previous command running?", commandQueue[indexer-1]->IsScheduled());
//         frc2::CommandScheduler::GetInstance().OnCommandFinish(
//         [this, commandQueue](const frc2::Command& command) {
//             if (command.GetName() == commandQueue[indexer-1]->GetName())
//                 commandQueue[indexer]->Schedule();
//             else
//                 --indexer;
//         });
//         frc::SmartDashboard::PutNumber("current indexer:", indexer);
//     }
// }

// void AutoCommandScheduler::ScheduleFirstCommand(std::vector<frc2::Command*> cmdList) {
//     cmdList[0]->Schedule();
// }

// void AutoCommandScheduler::AssignVacantPtrs(std::vector<frc2::Command*> cmdList, int indexer, int max) {
//     if (currCommand == nullptr)
//         currCommand = cmdList[indexer];
//     if (nextCommand == nullptr)
//         nextCommand = cmdList[indexer+1];
// }

// bool AutoCommandScheduler::IsFinished() {
//     return isFinished;
// }

// void AutoCommandScheduler::CleanPtrs() {
//     delete currCommand;
//     delete nextCommand;
//     currCommand = NULL;
//     nextCommand = NULL;

//     for (auto ptr : commandList) {
//         delete ptr;
//     }
//     commandList.clear();
// }