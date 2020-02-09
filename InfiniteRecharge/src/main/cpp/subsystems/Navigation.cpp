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
        leftDistance = ((Constants::Encoders::rotationMultiplier * Constants::Drivetrain::Gear::high) * leftEncoderPos) / Constants::Encoders::wheelCircum;
        rightEncoderPos = ((Constants::Encoders::rotationMultiplier * Constants::Drivetrain::Gear::high) * rightEncoderPos) / Constants::Encoders::wheelCircum;
    }
    else {
        leftDistance = ((Constants::Encoders::rotationMultiplier * Constants::Drivetrain::Gear::low) * leftEncoderPos) / Constants::Encoders::wheelCircum;
        rightEncoderPos = ((Constants::Encoders::rotationMultiplier * Constants::Drivetrain::Gear::low) * leftEncoderPos) / Constants::Encoders::wheelCircum;
    }
    return std::make_pair(leftDistance, rightDistance);
}