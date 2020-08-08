/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutonomousBallSeek.h"
#include "RobotContainer.h"

AutonomousBallSeek::AutonomousBallSeek() {}

void AutonomousBallSeek::Initialize() {
    turnToTarget->EnableTurningMode();
}

void AutonomousBallSeek::Execute() {
    if (turnToTarget->HasRobotTurned()) {
        if (!hasDriven) {
            turnToTarget->DisableTurningMode();
            SetDistanceToTargetAndDrive();
        }
        else {
            if (!intakeBall->IsScheduled())
                intakeBall->Schedule();
        }
    }
}

void AutonomousBallSeek::SetDistanceToTargetAndDrive() {
    if (inchesToTarget == 0) {
        inchesToTarget = RobotContainer::aiVisionTargetting->GetRobotDistToTarget();
        autoDrive->SetDist(inchesToTarget);
    }
    else
        DriveToTargetAndStop();
}

void AutonomousBallSeek::DriveToTargetAndStop() {
    if (autoDrive->HasReachedTargetDistance())
        hasDriven = true;
    else if (!autoDrive->IsScheduled())
        autoDrive->Schedule();
}

void AutonomousBallSeek::End(bool interrupted) {}

bool AutonomousBallSeek::IsFinished() { return false; }
