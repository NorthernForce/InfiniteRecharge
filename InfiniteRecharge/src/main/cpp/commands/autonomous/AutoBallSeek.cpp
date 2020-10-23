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
    inchesToTarget = 0;
}

void AutoBallSeek::Initialize() {
    turnToTarget->EnableTurningMode();
}

void AutoBallSeek::Execute() {
    if (turnToTarget->HasRobotTurned()) {
        RobotContainer::cameraMount->PauseSweep();
        if (!hasDriven) {
            turnToTarget->DisableTurningMode();
            turnToTarget->Cancel();
            SetDistanceToTargetAndDrive();
        }
    }
    else if (hasDriven) {
        if (!turnToAngle->IsScheduled() && !turnToAngleHasBeenScheduled) {
            double angleToTarget = RobotContainer::aiVisionTargetting->GetRobotAngleToTargetIntakeCam();
            turnToAngle->SetAngle(angleToTarget);
            turnToAngle->Schedule();
            turnToAngleHasBeenScheduled = true;
        }
        if (!intakeHasBeenScheduled && turnToAngleHasBeenScheduled) {
            intakeBall->Schedule();
            intakeHasBeenScheduled = true;
        }
    }
}

void AutoBallSeek::SetDistanceToTargetAndDrive() {
    inchesToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
    if (inchesToTarget != 0 && !distHasBeenSet) {
        std::pair<double, double> targetCoords = RobotContainer::aiVisionTargetting->GetFieldCoordinatesOfTarget();
        moveToCoordinate.reset(new MoveToCoordinate(targetCoords.first, targetCoords.second, 0.145));
        distHasBeenSet = true;
    }
    if (distHasBeenSet)
        DriveToTargetAndStop();
}

void AutoBallSeek::DriveToTargetAndStop() {
    if (RobotContainer::ultrasonic->GetDistance() < 18) {
        moveToCoordinate->Cancel();
        moveToCoordinate == nullptr;
    }
    if (moveToCoordinate != nullptr) {
        if (!driveHasBeenScheduled) {
            moveToCoordinate->Schedule();
            driveHasBeenScheduled = true;
        }
        else if  (!moveToCoordinate->IsScheduled()) {
            moveToCoordinate->Cancel();
            hasDriven = true;
        }
    }
    else
        this->Cancel();
}

void AutoBallSeek::End(bool interrupted) {
    intakeBall->Cancel();
    RobotContainer::cameraMount->ResumeSweep();
}

bool AutoBallSeek::IsFinished() {
    return (!intakeBall->IsScheduled() && intakeHasBeenScheduled);
}