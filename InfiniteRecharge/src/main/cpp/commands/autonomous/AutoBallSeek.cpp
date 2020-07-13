/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutoBallSeek.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"

AutoBallSeek::AutoBallSeek() {}

// Called when the command is initially scheduled.
void AutoBallSeek::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoBallSeek::Execute() {
    if (hasDriven) {
        if (intakeBall->IsFinished())
            hasCompletedIntake = true;
        else if (!intakeBall->IsScheduled())
            intakeBall->Schedule();
    }
    else if (turnToTarget->HasRobotTurned() && !hasDriven)
        DriveToTarget();

    else if (!turnToTarget->IsAutoTurningEnabled() && !turnToTarget->HasRobotTurned())
        turnToTarget->EnableTurningMode();
}

void AutoBallSeek::DriveToTarget() {
    if (!hasDriven) {
        distToTarget = RobotContainer::aiVisionTargetting->GetRobotDistToTarget();
        
        if (!autoDrive->IsScheduled() && distToTarget != 0) {
            autoDrive->SetDist(distToTarget);
            autoDrive->Schedule();
        }
        else if (autoDrive->HasReachedTargetDistance() && distToTarget != 0)
            hasDriven = true;
    }
}

// Called once the command ends or is interrupted.
void AutoBallSeek::End(bool interrupted) {
    turnToTarget->DisableTurningMode();
}

// Returns true when the command should end.
bool AutoBallSeek::IsFinished() { return hasCompletedIntake; }