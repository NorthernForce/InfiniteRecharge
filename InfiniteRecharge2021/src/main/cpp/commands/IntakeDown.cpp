/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeDown.h"
#include "RobotContainer.h"

IntakeDown::IntakeDown() {
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(RobotContainer::intake.get());
    safeCameraCmd = std::make_unique<SafeCamera>();
}

// Called when the command is initially scheduled.
void IntakeDown::Initialize() {
    safeCameraCmd->Schedule();
}

// Called repeatedly when this Command is scheduled to run
void IntakeDown::Execute() {
    if (!safeCameraCmd->IsScheduled())
        RobotContainer::intake->SetArm(0.35);
}

// Called once the command ends or is interrupted.
void IntakeDown::End(bool interrupted) {
    RobotContainer::intake->SetArm(0);
}

// Returns true when the command should end.
bool IntakeDown::IsFinished() { return false; }
