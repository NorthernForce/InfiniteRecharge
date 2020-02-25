/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/AIVisionTargetting.h"
#include "Constants.h"

AIVisionTargetting::AIVisionTargetting() {}

// This method will be called once per scheduler run
void AIVisionTargetting::Periodic() {}

// bool AIVisionTargetting::CheckForTarget() {
//     if (TargetFound)
//         return true;
// }
// Target AIVisionTargetting::CheckTargetType() {
//     switch(TargetType) {
//         case 0:
//             return Target::Powercell;
//             break;
//         case 1:
//             return Target::UpperGoal;
//             break;
//         case 2:
//             return Target::LowerGoal;
//             break;
//     }
// }

void AIVisionTargetting::RefreshTargetPositioning() {
    double currentPan = RobotContainer::cameraMount->GetCurrentPan();
    double powerCellOffsetX = RobotContainer::aiComms->GetValueArray(RobotContainer::aiComms->powercellOffsetInCam)[0];
    double camAngleToTarget = currentPan + powerCellOffsetX;
    double camDistToTarget = RobotContainer::aiComms->GetNumber(RobotContainer::aiComms->distanceToPcFromCam);
    camAngleToTarget *= Constants::degreesToRadians;

    targetPositionX = camDistToTarget * std::sin(camAngleToTarget);
    targetPositionY = camDistToTarget * std::cos(camAngleToTarget);
}

double AIVisionTargetting::RoboAngleToTarget() {
    RefreshTargetPositioning();
    return std::atan((targetPositionX-Constants::camDistFromRoboFrontCent)/(targetPositionY+Constants::camDistFromRoboSideCent));
}

double AIVisionTargetting::RoboDistToTarget() {
    RefreshTargetPositioning();
    return sqrt(pow((targetPositionY+Constants::camDistFromRoboFrontCent),2.0)+pow((Constants::camDistFromRoboSideCent-targetPositionX),2.0));
}


// double TargDist(double Ac,double Dc)
// {
//     Ac *= (M_PI/180);
//     double C = 10;
//     double Tx = Dc*std::sin(Ac);
//     double Ty = Dc*std::cos(Ac);
//     double Td = sqrt(pow(Ty,2.0)+pow((C-Tx),2.0));

//     return Td;
// }

// double TargAng(double Ac,double Dc)
// {
//     Ac *= conve;
//     double C = 10;
//     double Tx = Dc*std::sin(Ac);
//     double Ty = Dc*std::cos(Ac);
//     double Ta = std::atan((Tx-C)/Ty);

//     Ta /= convert;

//     return Ta;
// }