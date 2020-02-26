/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Navigation.h"
#include "RobotContainer.h"

Navigation::Navigation() {}


////TODO: Need to calculate position
// This method will be called once per scheduler run
void Navigation::Periodic() {
    robotCurrentAngle = RobotContainer::imu->GetRotation();
    averageSpeedInRPM = (RobotContainer::drivetrain->GetLeftRPM() + RobotContainer::drivetrain->GetRightRPM() / 2);
    std::cout << "EncoderPos" << RobotContainer::drivetrain->GetEncoderRotations().first;
}

std::pair<double, double> Navigation::GetInchesTravelled() {
    double leftEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().first;
    double rightEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().second;
    double leftDistance;
    double rightDistance;

    if (RobotContainer::driveShifter->GetGear() == DriveShifter::Gear::High) {
        leftDistance = leftEncoderPos * Constants::Shifting::highMultiplier;
        rightDistance = rightEncoderPos * Constants::Shifting::highMultiplier;
    }
    else {
        leftDistance = leftEncoderPos * Constants::Shifting::lowMultiplier;
        rightDistance = rightEncoderPos * Constants::Shifting::lowMultiplier;
    }
    return std::make_pair(leftDistance, rightDistance);
}