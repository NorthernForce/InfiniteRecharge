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
    RobotContainer::aiComms->SwitchCameraToGimbal();
    RobotContainer::cameraMount->ResumeSweep();
    inchesToTarget = 0;
    hasTurned = false;
    hasDriven = false;
    distHasBeenSet = false;
    driveHasBeenScheduled = false;
    intakeHasBeenScheduled = false;
    turnToAngleHasBeenScheduled = false;

    turnToTarget->EnableTurningMode();
}

void AutoBallSeek::Execute() {
    frc::SmartDashboard::PutBoolean("hasDriven", hasDriven);
    if (turnToTarget->HasRobotTurned())
        hasTurned = true;

    if (hasTurned && !hasDriven) {
        RobotContainer::cameraMount->PauseSweep();
        RobotContainer::cameraMount->Pan(90);
        turnToTarget->DisableTurningMode();
        SetDistanceToTargetAndDrive();
    }
    else if (hasDriven) {
        RobotContainer::aiComms->SwitchCameraToIntake();
        if (!turnToAngle->IsScheduled() && !turnToAngleHasBeenScheduled) {
            double angleToTarget = RobotContainer::aiVisionTargetting->GetRobotAngleToTargetIntakeCam();
            frc::SmartDashboard::PutNumber("angleInIntakeCam", angleToTarget);
            if (angleToTarget != 0) {
                turnToAngle->SetAngle(angleToTarget);
                turnToAngle->Schedule();
                turnToAngleHasBeenScheduled = true;
            }
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
        if (targetCoords.first != 0 || targetCoords.second != 0) {
            moveToCoordinate.reset(new MoveToCoordinate(targetCoords.first, targetCoords.second, 0.145));
            distHasBeenSet = true;
        }
    }
    if (distHasBeenSet)
        DriveToTargetAndStop();
}

void AutoBallSeek::DriveToTargetAndStop() {
    if (!driveHasBeenScheduled){
        moveToCoordinate->Schedule();
        driveHasBeenScheduled = true;
    }
    else if (moveToCoordinate->GetIsFinished() || !moveToCoordinate->IsScheduled()) {
        RobotContainer::aiComms->SwitchCameraToIntake();
        moveToCoordinate->Cancel();
        hasDriven = true;
    }
}

void AutoBallSeek::End(bool interrupted) {
    intakeBall->Cancel();
    RobotContainer::aiComms->SwitchCameraToGimbal();
    RobotContainer::cameraMount->ResumeSweep();
}

bool AutoBallSeek::IsFinished() {
    return intakeBall->GetIsFinished();
}