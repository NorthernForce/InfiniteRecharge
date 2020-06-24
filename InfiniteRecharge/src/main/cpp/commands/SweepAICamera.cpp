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
    turnToAngle = std::make_shared<TurnToAngle>();
}

// Called when the command is initially scheduled.
void SweepAICamera::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
}

// Called repeatedly when this Command is scheduled to run
void SweepAICamera::Execute() {
    RobotContainer::cameraMount->SmartSweep();
    bool isTargetPresent = RobotContainer::aiVisionTargetting->CheckForTarget(powercell);
    if (isTargetPresent)
        TurnRobotToTarget();
}

void SweepAICamera::TurnRobotToTarget() {
    double pcOffsetInCamera = RobotContainer::aiComms->GetCamTargetOffsets(powercell)[0];
    double targetAng = RobotContainer::aiVisionTargetting->GetRobotAngleToTarget();

    if (RobotContainer::oi->driverController->GetRawButton(OI::Xbox::menu_button)) {
        TurnWithButtonToAng(targetAng);
        hasturnedOnButton = true;
    }
    else
        hasturnedOnButton = false;
}

void SweepAICamera::TurnWithButtonToAng(int ang) {
    if (!turnToAngle->IsScheduled() && !hasturnedOnButton) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
    }
}

// Called once the command ends or is interrupted.
void SweepAICamera::End(bool interrupted) {}

// Returns true when the command should end.
bool SweepAICamera::IsFinished() { return false; }