// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ParallelCommand.h"

ParallelCommand::ParallelCommand(std::vector<frc2::Command*> commands)
 : commands(commands) {}

void ParallelCommand::Initialize() {
    for (frc2::Command* command : commands) {
        command->Schedule();
    }
    commandsHaveBeenScheduled = true;
}

void ParallelCommand::Execute() {}

void ParallelCommand::End(bool interrupted) {}

bool ParallelCommand::IsFinished() {
    unsigned i = 0;
    for (frc2::Command* command : commands) {
        if (!command->IsScheduled())
            i++;
    }
    return ((i == commands.size()) && commandsHaveBeenScheduled);
}
