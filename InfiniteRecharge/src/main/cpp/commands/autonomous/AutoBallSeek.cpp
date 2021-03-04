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
}

void AutoBallSeek::Execute() {
    if (driveHasBeenScheduled && !moveToCoordinate->IsScheduled()) {
        moveToCoordinate->Cancel();
        hasDriven = true;
    }

    currentEncoder = RobotContainer::drivetrain->GetEncoderRotations().first;

    if (turnToTarget->HasRobotTurned() && !hasDriven) {
        RobotContainer::cameraMount->PauseSweep();
        RobotContainer::cameraMount->Pan(90);
        turnToTarget->DisableTurningMode();
        turnToTarget->Cancel();
        SetDistanceToTargetAndDrive();
    }
    // else if (hasDriven) {
    //     intakeHasBeenScheduled = true;
    //     intakeBall->Schedule();
    //     // if (!turnToAngle->IsScheduled() && !turnToAngleHasBeenScheduled) {
    //     //     double angleToTarget = RobotContainer::aiVisionTargetting->GetRobotAngleToTargetIntakeCam();
    //     //     if (angleToTarget != 0) {
    //     //         turnToAngle->SetAngle(angleToTarget);
    //     //         turnToAngle->Schedule();
    //     //         turnToAngleHasBeenScheduled = true;
    //     //     }
    //     // }
    //     if (!intakeHasBeenScheduled) {
    //         intakeBall->Schedule();
    //         intakeHasBeenScheduled = true;
    //     }
    // }

    previousEncoder = currentEncoder;
}

void AutoBallSeek::SetDistanceToTargetAndDrive() {
    inchesToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
    if (inchesToTarget != 0 && !distHasBeenSet) {
        std::pair<double, double> targetCoords = RobotContainer::aiVisionTargetting->GetFieldCoordinatesOfTarget();
        //RobotContainer::aiComms->SwitchCameraToIntake();
        moveToCoordinate.reset(new MoveToCoordinate(targetCoords.first, targetCoords.second, 0.145));
        distHasBeenSet = true;
    }
    if (distHasBeenSet) {
        DriveToTargetAndStop();
        intakeBall->Schedule();
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
    RobotContainer::aiComms->SwitchCameraToGimbal();
    RobotContainer::cameraMount->ResumeSweep();
}

bool AutoBallSeek::IsFinished() {
    return (!intakeBall->IsScheduled() && intakeHasBeenScheduled);
}