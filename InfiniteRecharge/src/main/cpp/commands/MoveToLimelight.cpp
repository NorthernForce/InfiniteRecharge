/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveToLimelight.h"
#include "commands/TurnToAngle.h"
#include <frc2/command/Command.h>
#include <frc2/command/ScheduleCommand.h>
#include "ctre/Phoenix.h"
#include "RobotContainer.h"
#include <iostream>

MoveToLimelight::MoveToLimelight() {
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(RobotContainer::limelight.get());
}

// Called when the command is initially scheduled.
void MoveToLimelight::Initialize() {
    RobotContainer::limelight->PutNumberToTable("ledMode", 3);
}

// Called repeatedly when this Command is scheduled to run
void MoveToLimelight::Execute() {
    limeLightOffset = RobotContainer::limelight->GetXOffset();
    int limeLightOffsetI = (int) limeLightOffset;
    isTargetThere = RobotContainer::limelight->IsTargetThere();

    if (isTargetThere == true) {
        if(limeLightOffset > 3) {
                RobotContainer::shooter->SetSusanSpeed(0.4);
        } else if (limeLightOffset <= -3) {
                RobotContainer::shooter->SetSusanSpeed(-0.4);
        } else {
                RobotContainer::shooter->SetSusanSpeed(-0);
        }

    }
    
}

// Called once the command ends or is interrupted.
void MoveToLimelight::End(bool interrupted) {
    if(limeLightOffset >= -3 && limeLightOffset <= 3){
        std::cout << "done";
    //RobotContainer::limelight->PutNumberToTable("ledMode", 1); 
    }
    }

// Returns true when the command should end.
bool MoveToLimelight::IsFinished() {}
