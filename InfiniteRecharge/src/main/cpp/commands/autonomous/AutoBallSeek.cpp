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
    RobotContainer::cameraMount->ResumeSweep();
    RobotContainer::aiComms->SwitchCameraToGimbal();
    turnToTarget->EnableTurningMode();
    intakeTimer->Reset();
}

void AutoBallSeek::Execute() {
    if (driveHasBeenScheduled && !moveToCoordinate->IsScheduled()) {
        moveToCoordinate->Cancel();
        hasDriven = true;
    }

    if (turnToTarget->HasRobotTurned() && !hasDriven) {
        RobotContainer::cameraMount->PauseSweep();
        RobotContainer::cameraMount->Pan(90);
        turnToTarget->DisableTurningMode();
        turnToTarget->Cancel();
        SetDistanceToTargetAndDrive();
    }
}

void AutoBallSeek::SetDistanceToTargetAndDrive() {
    inchesToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
    if (inchesToTarget != 0 && !distHasBeenSet) {
        std::pair<double, double> targetCoords = RobotContainer::aiVisionTargetting->GetFieldCoordinatesOfTarget();
        moveToCoordinate.reset(new MoveToCoordinate(targetCoords.first, targetCoords.second, 0.145));
        distHasBeenSet = true;
    }
    if (distHasBeenSet) {
        DriveToTargetAndStop();
        intakeBall->Schedule();
        intakeHasBeenScheduled = true;
        intakeTimer->Start();
    }  
}

void AutoBallSeek::DriveToTargetAndStop() {
    if (driveHasBeenScheduled && !moveToCoordinate->IsScheduled()) {
        moveToCoordinate->Cancel();
        hasDriven = true;
    }
    else {
        moveToCoordinate->Schedule();
        driveHasBeenScheduled = true;
    }
}

void AutoBallSeek::End(bool interrupted) {
    intakeBall->Cancel();
    intakeTimer->Stop();
    RobotContainer::aiComms->SwitchCameraToGimbal();
    RobotContainer::cameraMount->ResumeSweep();
}

bool AutoBallSeek::IsFinished() {
    return ((!intakeBall->IsScheduled() && intakeHasBeenScheduled) || intakeTimer->Get() > 10);
}