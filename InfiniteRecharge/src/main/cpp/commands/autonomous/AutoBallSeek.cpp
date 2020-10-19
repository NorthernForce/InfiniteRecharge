/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutoBallSeek.h"
#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>

AutoBallSeek::AutoBallSeek() {
    distHasBeenSet = false;
    driveHasBeenScheduled = false;
    inchesToTarget = 0;
}

void AutoBallSeek::Initialize() {
    turnToTarget->EnableTurningMode();
}

void AutoBallSeek::Execute() {
    if (turnToTarget->HasRobotTurned()) {
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

void AutoBallSeek::SetDistanceToTargetAndDrive() {
    inchesToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
    if (inchesToTarget != 0 && !distHasBeenSet) {
        std::pair<double, double> targetCoords = RobotContainer::aiVisionTargetting->GetFieldCoordinatesOfTarget();
        frc::SmartDashboard::PutNumber("aiMoveToX", targetCoords.first);
        frc::SmartDashboard::PutNumber("aiMoveToY", targetCoords.second);
        moveToCoordinate.reset(new MoveToCoordinate(targetCoords.first, targetCoords.second, 0.145));
        distHasBeenSet = true;
    }
    if (distHasBeenSet)
        DriveToTargetAndStop();
}

void AutoBallSeek::DriveToTargetAndStop() {
    if (!driveHasBeenScheduled) {
        moveToCoordinate->Schedule();
        driveHasBeenScheduled = true;
    }
    else if  (!moveToCoordinate->IsScheduled()) {
        moveToCoordinate->Cancel();
        hasDriven = true;
    }
}

void AutoBallSeek::End(bool interrupted) {
    intakeBall->Cancel();
}

bool AutoBallSeek::IsFinished() {
    return (!intakeBall->IsScheduled() && intakeHasBeenScheduled);
}
