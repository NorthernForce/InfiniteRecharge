/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Navigation.h"
#include "RobotContainer.h"

Navigation::Navigation() {}

// This method will be called once per scheduler run
void Navigation::Periodic() {
    robotCurrentAngle = RobotContainer::imu->GetRotation();
    averageSpeedInRPM = (RobotContainer::drivetrain->GetLeftRPM() + RobotContainer::drivetrain->GetRightRPM() / 2);
    // std::cout << "Distance Travelled- L: " << GetInchesTravelled().first << '\n';
    // std::cout << "Distance travelled- R: " << GetInchesTravelled().second << '\n';
}

std::pair<double, double> Navigation::GetInchesTravelled() {
    double leftEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().first;
    double rightEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().second;
    double leftDistance;
    double rightDistance;

    if (RobotContainer::driveShifter->GetGearAsInt() == 1) {
        leftDistance = ((5.88) * leftEncoderPos)/Constants::Encoders::wheelCircumference;
        rightEncoderPos = (5.88 * rightEncoderPos)/Constants::Encoders::wheelCircumference;
    }
    else {
        leftDistance = (21.43 * leftEncoderPos)/Constants::Encoders::wheelCircumference;
        rightEncoderPos = (21.43 * rightEncoderPos)/Constants::Encoders::wheelCircumference;
    }
    return std::make_pair(leftDistance, rightDistance);
}