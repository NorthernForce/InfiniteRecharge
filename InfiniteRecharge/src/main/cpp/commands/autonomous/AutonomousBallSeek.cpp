/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutonomousBallSeek.h"
#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>

AutonomousBallSeek::AutonomousBallSeek() {
    distHasBeenSet = false;
    driveHasBeenScheduled = false;
    inchesToTarget = 0;
}

void AutonomousBallSeek::Initialize() {
    turnToTarget->EnableTurningMode();
}

void AutonomousBallSeek::Execute() {
    // int averageCameraPan = RobotContainer::cameraMount->GetAvgOfRecentPans();
    // bool ballIsCentered = averageCameraPan > 85 && averageCameraPan < 95;
    double angleToTarget = RobotContainer::aiVisionTargetting->GetRobotAngleToTarget();
    bool ballIsCentered = abs(angleToTarget) < 3;

    if (turnToTarget->HasRobotTurned() && ballIsCentered) {
        if (!hasDriven) {
            turnToTarget->DisableTurningMode();
            turnToTarget->Cancel();
            SetDistanceToTargetAndDrive();
        }
    } else if (turnToTarget->HasRobotTurned()) {
        turnToTarget->Reset();
        turnToTarget->EnableTurningMode();
    }
    else if (hasDriven) {
        if (!intakeHasBeenScheduled) {
            intakeBall->Schedule();
            intakeHasBeenScheduled = true;
        }
    }
}

void AutonomousBallSeek::SetDistanceToTargetAndDrive() {
    inchesToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
    if (inchesToTarget != 0) {
        autoDrive->SetDist(inchesToTarget);
        distHasBeenSet = true;
    }
    if (distHasBeenSet)
        DriveToTargetAndStop();
}

void AutonomousBallSeek::DriveToTargetAndStop() {
    if (!driveHasBeenScheduled) {
        autoDrive->Schedule();
        driveHasBeenScheduled = true;
    }
    else if  (autoDrive->HasReachedTargetDistance() && autoDrive->GetDist() != 0) {
        autoDrive->Cancel();
        hasDriven = true;
    }
}

void AutonomousBallSeek::End(bool interrupted) {
    intakeBall->Cancel();
}

bool AutonomousBallSeek::IsFinished() {
    return (!intakeBall->IsScheduled() && intakeHasBeenScheduled);
}
