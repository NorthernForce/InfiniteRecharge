/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* <-- Remove Once Ready

#include "subsystems/AIVisionTargetting.h"
#include "RobotContainer.h"

AIVisionTargetting::AIVisionTargetting() {}

bool AIVisionTargetting::CheckForTarget() {
    if (TargetFound)
        return true;
}
Target AIVisionTargetting::CheckTargetType() {
    switch(TargetType) {
        case 0:
            return Target::Powercell;
            break;
        case 1:
            return Target::UpperGoal;
            break;
        case 2:
            return Target::LowerGoal;
            break;
    }
}

int AIVisionTargetting::GetAngleOfTarget() {
    return RobotContainer::cameraMount->GetServoAngleToTarget();
}

double GetTargetOffsetInCamera() {

}

// This method will be called once per scheduler run
void AIVisionTargetting::Periodic() {}

*/