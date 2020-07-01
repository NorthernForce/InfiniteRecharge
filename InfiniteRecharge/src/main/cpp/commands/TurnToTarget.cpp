/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToTarget.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

TurnToTarget::TurnToTarget() {
    AddRequirements(RobotContainer::cameraMount.get());
    AddRequirements(RobotContainer::aiVisionTargetting.get());
    turnToAngle = std::make_shared<TurnToAngle>();
    frc::SmartDashboard::PutBoolean("targetHasBeenLocked", RobotContainer::aiVisionTargetting->IsTargetLocked());
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
}

void TurnToTarget::EnableTurningMode(bool enableTurning) {
    turningMode = enableTurning;
}

bool TurnToTarget::IsTurningEnabled() {
    return (RobotContainer::oi->driverController->GetRawButton(OI::Xbox::menu_button) or turningMode);
}

// Called repeatedly when this Command is scheduled to run
void TurnToTarget::Execute() {
    RobotContainer::cameraMount->SmartSweep();
    bool isTargetPresent = RobotContainer::aiVisionTargetting->CheckForTarget(powercell);
    if (isTargetPresent)
        TurnRobotToTarget();
}

void TurnToTarget::TurnRobotToTarget() {
    double targetAng = RobotContainer::aiVisionTargetting->GetRobotAngleToTarget();

    if (IsTurningEnabled()) {
        TurnToAng(targetAng);
        if (!turnToAngle->IsScheduled())
            hasTurned = true;
    }
    else
        hasTurned = false;
}

void TurnToTarget::TurnToAng(int ang) {
    if (!turnToAngle->IsScheduled() && !hasTurned) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
    }
}

bool TurnToTarget::HasReachedTargetAngle() {
    return hasTurned;
}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() { return false; }