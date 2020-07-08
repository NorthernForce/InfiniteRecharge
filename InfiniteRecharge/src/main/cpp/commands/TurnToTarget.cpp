/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToTarget.h"

bool TurnToTarget::turningMode;
bool TurnToTarget::hasTurned;

TurnToTarget::TurnToTarget() {
    AddRequirements(RobotContainer::cameraMount.get());
    AddRequirements(RobotContainer::aiVisionTargetting.get());
    turnToAngle = std::make_shared<TurnToAngle>();
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
    turningMode = false;
}

void TurnToTarget::EnableTurningMode() {
    turningMode = true;
}

void TurnToTarget::DisableTurningMode() {
    turningMode = false;
}

bool TurnToTarget::IsTurnOnButtonEnabled() {
    return (RobotContainer::oi->driverController->GetRawButton(OI::XboxPOV::down) > 0.5);
}

bool TurnToTarget::IsAutoTurningEnabled() {
    return turningMode;
}

// Called repeatedly when this Command is scheduled to run
void TurnToTarget::Execute() {
    RobotContainer::cameraMount->SmartSweep();
    bool isTargetLocked = RobotContainer::aiVisionTargetting->IsTargetLocked();
    if (isTargetLocked)
        TurnRobotToTarget();
}

void TurnToTarget::TurnRobotToTarget() {
    if (IsTurnOnButtonEnabled() or IsAutoTurningEnabled()) {
        double targetAng = RobotContainer::aiVisionTargetting->GetRobotAngleToTarget();
        TurnToAng(targetAng);
    }
    if (abs(turnToAngle->GetCurrentError()) < turnToAngle->GetMinimumError())
        hasTurned = true;
}

void TurnToTarget::TurnToAng(int ang) {
    if (!turnToAngle->IsScheduled()) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
    }
}

bool TurnToTarget::HasRobotTurned() {
    return hasTurned;
}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() { return false; }