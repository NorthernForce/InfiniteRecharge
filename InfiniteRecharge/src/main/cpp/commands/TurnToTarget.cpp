/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToTarget.h"

bool TurnToTarget::turningMode;
bool TurnToTarget::hasTurned;
int TurnToTarget::distanceToTargetBeforeTurn;
////TODO: make not static if possible

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
    return (RobotContainer::oi->manipulatorController->GetRawButton(OI::Xbox::menu_button));
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
    if (IsTurnOnButtonEnabled() or IsAutoTurningEnabled())
        TurnToAng(targetAng);
}

void TurnToTarget::TurnToAng(int ang) {
    if (distanceToTargetBeforeTurn == 0)
        distanceToTargetBeforeTurn = RobotContainer::aiVisionTargetting->GetRobotDistToTarget();

    if (!turnToAngle->IsScheduled() && ang != 0 && !hasStartedTurn) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
        hasStartedTurn = true;
    }      

    hasTurned = (turnToAngle->GetIsFinished() && hasStartedTurn && distanceToTargetBeforeTurn != 0 && !turnToAngle->IsScheduled());  
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
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() { return false; }