/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToTarget.h"
#include <iostream>

TurnToTarget::TurnToTarget() {
    AddRequirements(RobotContainer::cameraMount.get());
    AddRequirements(RobotContainer::aiVisionTargetting.get());
    turnToAngle = std::make_shared<TurnToAngle>();
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {
    RobotContainer::cameraMount->Tilt(0);
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

    if (RobotContainer::oi->driverController->GetRawButton(OI::Xbox::menu_button)) {
        TurnWithButtonToAng(targetAng);
        hasturnedOnButton = true;
    }
    else
        hasturnedOnButton = false;
}

void TurnToTarget::TurnWithButtonToAng(int ang) {
    if (!turnToAngle->IsScheduled() && !hasturnedOnButton) {
        turnToAngle->SetAngle(ang);
        turnToAngle->Schedule();
        RobotContainer::cameraMount->Pan(90);
    }
}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() { return false; }