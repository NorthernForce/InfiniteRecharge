/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"

bool TurnToTarget::turningMode;
bool TurnToTarget::hasTurned;
int TurnToTarget::distanceToTargetBeforeTurn;

TurnToTarget::TurnToTarget() {
    AddRequirements(RobotContainer::cameraMount.get());
    AddRequirements(RobotContainer::aiVisionTargetting.get());
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
    RobotContainer::cameraMount->Pan(90);
    Reset();
}

void TurnToTarget::EnableTurningMode() {
    turningMode = true;
}

void TurnToTarget::DisableTurningMode() {
    turningMode = false;
}

bool TurnToTarget::IsTurnOnButtonEnabled() {
    if (hasTurned)
        Reset();
    return RobotContainer::oi->manipulatorController->GetRawButton(OI::Xbox::menu_button);
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
    double targetAng = RobotContainer::aiVisionTargetting->GetRobotAngleToTarget();
    frc::SmartDashboard::PutNumber("angleToTarget", targetAng);
    if (IsTurnOnButtonEnabled() || IsAutoTurningEnabled())
        TurnToAng(targetAng);
}

void TurnToTarget::TurnToAng(double ang) {
    if (distanceToTargetBeforeTurn == 0)
        distanceToTargetBeforeTurn = 0.85 * RobotContainer::aiVisionTargetting->GetRobotDistToTarget();

    if (ang != 0 && !hasStartedTurn) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
        hasStartedTurn = true;
    }

    if (distanceToTargetBeforeTurn != 0)
        hasTurned = (turnToAngle->GetIsFinished() && hasStartedTurn);
}

int TurnToTarget::GetDistanceToTargetBeforeTurn() {
    return distanceToTargetBeforeTurn;
}

bool TurnToTarget::HasRobotTurned() {
    return hasTurned;
}

bool TurnToTarget::IsTurningScheduled() {
    return turnToAngle->IsScheduled();
}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {
    hasStartedTurn = false;
}

void::TurnToTarget::Reset() {
    turningMode = false;
    hasTurned = false;
    hasStartedTurn = false;
    distanceToTargetBeforeTurn = 0;
    turnToAngle.reset(new TurnToAngle);
}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() { return false; }