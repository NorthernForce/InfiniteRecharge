/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToTarget.h"

bool TurnToTarget::hasTurned;
bool TurnToTarget::turningMode;
bool TurnToTarget::startedTurning;


TurnToTarget::TurnToTarget() {
    AddRequirements(RobotContainer::cameraMount.get());
    AddRequirements(RobotContainer::aiVisionTargetting.get());
    turnToAngle = std::make_shared<TurnToAngle>();
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
    turningMode = false;
    startedTurning = false;
    hasTurned = false;
}

void TurnToTarget::EnableTurningMode() {
    turningMode = true;
}

void TurnToTarget::DisableTurningMode() {
    turningMode = false;
}

bool TurnToTarget::IsTurnOnButtonEnabled() {
    return RobotContainer::oi->driverController->GetRawButton(OI::Xbox::menu_button);
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
        std::cout << "hasTurned: " << (!turnToAngle->IsScheduled() && startedTurning) << '\n';
        if (!turnToAngle->IsScheduled() && startedTurning)
            hasTurned = true;
    }
    else
        hasTurned = false;
}

void TurnToTarget::TurnToAng(int ang) {
    if (!turnToAngle->IsScheduled()) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
        startedTurning = true;
    }
}

bool TurnToTarget::HasReachedTargetAngle() {
    return hasTurned;
}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() { return false; }