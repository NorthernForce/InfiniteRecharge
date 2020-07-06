/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutoBallSeek.h"
#include "RobotContainer.h"

AutoBallSeek::AutoBallSeek() {}

// Called when the command is initially scheduled.
void AutoBallSeek::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoBallSeek::Execute() {
    if (!turnToTarget->IsAutoTurningEnabled())
        turnToTarget->EnableTurningMode();

    if (turnToTarget->HasReachedTargetAngle())
        DriveToTarget();
}

void AutoBallSeek::DriveToTarget() {
    // if (!hasDriven) {
    distToTarget = RobotContainer::aiVisionTargetting->GetRobotDistToTarget();
    autoDrive->SetDist(distToTarget);
    if (autoDrive->IsFinished())
        hasDriven = true;
    else if (!autoDrive->IsScheduled())
        autoDrive->Schedule();
    // }
}

// Called once the command ends or is interrupted.
void AutoBallSeek::End(bool interrupted) {
    turnToTarget->DisableTurningMode();
}

// Returns true when the command should end.
bool AutoBallSeek::IsFinished() { return false; }