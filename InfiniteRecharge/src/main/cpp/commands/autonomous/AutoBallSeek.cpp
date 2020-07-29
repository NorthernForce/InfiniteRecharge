/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutoBallSeek.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"

AutoBallSeek::AutoBallSeek() {}

// Called when the command is initially scheduled.
void AutoBallSeek::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoBallSeek::Execute() {
    if (turnToTarget->HasRobotTurned()) {
        if (!turnToTarget->IsAutoTurningEnabled())
            turnToTarget->EnableTurningMode();
    }
    if (turnToTarget->HasRobotTurned() && !turnToTarget->IsTurningScheduled()) {
        if (hasDriven)
            intakeBall->Schedule();
        else
            DriveToTarget();
    }
}

void AutoBallSeek::DriveToTarget() {
    if (!hasGottenDistToTarget) {
        distToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
        frc::SmartDashboard::PutNumber("distToTarget", distToTarget);
        autoDrive->SetDist(0.8*distToTarget);
        if (distToTarget != 0)
            hasGottenDistToTarget = true;
    }

    if (!hasStartedDriving) {
        autoDrive->Schedule();
        hasStartedDriving = true;
    }    
    if (autoDrive->HasReachedTargetDistance() && autoDrive->GetDist() > 0)
        hasDriven = true;

}

// Called once the command ends or is interrupted.
void AutoBallSeek::End(bool interrupted) {
    turnToTarget->DisableTurningMode();
}

// Returns true when the command should end.
bool AutoBallSeek::IsFinished() { return hasCompletedIntake; }