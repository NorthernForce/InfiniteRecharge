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
    frc::SmartDashboard::PutBoolean("HasRobotTurned: ", turnToTarget->HasRobotTurned());
    if (!turnToTarget->HasRobotTurned()) {
        if (!turnToTarget->IsAutoTurningEnabled())
            turnToTarget->EnableTurningMode();
    }
    else if (turnToTarget->HasRobotTurned() && !turnToTarget->IsTurningScheduled()) {
        if (!hasDriven)
            DriveToTarget();
        else if (hasDriven)
            intakeBall->Schedule();
    }
}

void AutoBallSeek::DriveToTarget() {
    if (!hasGottenDistToTarget) {
        distToTarget = turnToTarget->GetDistanceToTargetBeforeTurn();
        frc::SmartDashboard::PutNumber("distToTarget", distToTarget);
        autoDrive->SetDist(0.75*distToTarget);
        if (distToTarget != 0)
            hasGottenDistToTarget = true;
    }

    if (!autoDrive->IsScheduled() && !hasStartedDriving) {
        autoDrive->Schedule();
        hasStartedDriving = true;
    }    
    if (autoDrive->HasReachedTargetDistance() && distToTarget != 0)
        hasDriven = true;

}

// Called once the command ends or is interrupted.
void AutoBallSeek::End(bool interrupted) {
    turnToTarget->DisableTurningMode();
}

// Returns true when the command should end.
bool AutoBallSeek::IsFinished() { return hasCompletedIntake; }