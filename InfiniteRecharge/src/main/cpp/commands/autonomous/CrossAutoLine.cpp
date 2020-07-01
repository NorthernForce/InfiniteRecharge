/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/CrossAutoLine.h"
#include "commands/AutoDrive.h"
#include <memory>

CrossAutoLine::CrossAutoLine() {}

void CrossAutoLine::Initialize() {
    autoCommandScheduler.reset(new AutoCommandScheduler({
        new AutoDrive(36)
    }));
}

void CrossAutoLine::Execute() {
    autoCommandScheduler->Run();
}

bool CrossAutoLine::IsFinished() {
    return autoCommandScheduler->IsFinished();
}