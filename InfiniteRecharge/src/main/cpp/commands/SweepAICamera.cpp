/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SweepAICamera.h"
#include "commands/TurnToAngle.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

SweepAICamera::SweepAICamera() {
    AddRequirements(RobotContainer::cameraMount.get());
    AddRequirements(RobotContainer::aiVisionTargetting.get());
    turnToAngle.reset(new TurnToAngle());
}

// Called when the command is initially scheduled.
void SweepAICamera::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
}

// Called repeatedly when this Command is scheduled to run
void SweepAICamera::Execute() {
    if (RobotContainer::aiVisionTargetting->CheckForTarget(powercell))
        TurnRobotToTarget();
    else
        RobotContainer::cameraMount->Sweep();
}

void SweepAICamera::TurnRobotToTarget() {
    int servoPanAng = RobotContainer::cameraMount->GetCurrentPan();
    char servoPanDir = RobotContainer::cameraMount->GetPanDirection();
    double pcOffsetInCamera = RobotContainer::aiComms->GetCamTargetOffsets(powercell)[0];

    AdjustServoAngToPCOffset(servoPanAng, pcOffsetInCamera);
    if (OI::driverController->GetRawButton(OI::Xbox::menu_button))
        TurnRobotToServoAngle(servoPanAng, servoPanDir);
}

void SweepAICamera::AdjustServoAngToPCOffset(int servoAng, double pcOffset) {
    frc::SmartDashboard::PutNumber("pc offset", pcOffset);
    if (pcOffset < -10)
        RobotContainer::cameraMount->Pan(++servoAng);
    if (pcOffset > 10)
        RobotContainer::cameraMount->Pan(--servoAng);
}

void SweepAICamera::TurnRobotToServoAngle(int servoAng, char servoDir) {
    int robotAng = RobotContainer::imu->GetRotation();
    // if (servoDir == 'l')
    //     turnToAngle->SetAngle(robotAng+servoAng-90);
    // else if (servoDir == 'r')
    turnToAngle->SetAngle(-1*(servoAng-90));
        
    if (!turnToAngle->IsScheduled())
        turnToAngle->Schedule();
}

// Called once the command ends or is interrupted.
void SweepAICamera::End(bool interrupted) {}

// Returns true when the command should end.
bool SweepAICamera::IsFinished() { return false; }