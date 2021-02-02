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
    timer->Reset();
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
        if (!timerHasStarted) {
            timer->Start();
            timerHasStarted = true;
        }

        RobotContainer::aiComms->SwitchCameraToIntake();
        if (!turnToAngle->IsScheduled() && !turnToAngleHasBeenScheduled) {
            double angleToTarget = RobotContainer::aiVisionTargetting->GetRobotAngleToTargetIntakeCam();
            anglesToTarget.push_back(angleToTarget);

            frc::SmartDashboard::PutNumber("angleInIntakeCam", angleToTarget);
            if (timer->Get() > 0.5) {
                double medianAngleToTarget = CalculateMedian(anglesToTarget);

                if (medianAngleToTarget != 0) {
                    turnToAngle->SetAngle(medianAngleToTarget);
                    turnToAngle->Schedule();
                    turnToAngleHasBeenScheduled = true;

                    timer->Stop();
                    timer->Reset();
                    anglesToTarget.clear();
                }
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

double AutoBallSeek::CalculateMedian(std::vector<double> array) {
    size_t size = array.size();

    if (size == 0)
        return 0;

    else {
        sort(array.begin(), array.end());
        if (size % 2 == 0)
            return (array[size / 2 - 1] + array[size / 2]) / 2;
        else 
            return array[size / 2];
    }
}

void AutoBallSeek::DriveToTargetAndStop() {
    if (!driveHasBeenScheduled) {
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