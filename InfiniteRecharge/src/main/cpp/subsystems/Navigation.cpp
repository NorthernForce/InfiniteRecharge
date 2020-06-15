/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Navigation.h"
#include "RobotContainer.h"
#include "Constants.h"

#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Navigation::Navigation() {}

////TODO: Need to calculate position
// This method will be called once per scheduler run
void Navigation::Periodic() {
    robotCurrentAngle = RobotContainer::imu->GetRotation();
    averageSpeedInRPM = (RobotContainer::drivetrain->GetLeftRPM() + RobotContainer::drivetrain->GetRightRPM() / 2);
    CoordinatePosition();
    // std::cout << "EncoderPos" << RobotContainer::drivetrain->GetEncoderRotations().first;
}

std::pair<double, double> Navigation::GetInchesTravelled() {
    double leftEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().first - previousLeftEncoder;
    double rightEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().second - previousRightEncoder;
    previousLeftEncoder = RobotContainer::drivetrain->GetEncoderRotations().first;
    previousRightEncoder = RobotContainer::drivetrain->GetEncoderRotations().second;
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

void Navigation::ResetPosition() {
  xPosition = RobotContainer::aiComms->GetNumber(RobotContainer::aiComms->distanceToPcFromCam_label) * NavXScaling * abs(cos(robotAngleDifference));
  yPosition = RobotContainer::ultrasonic->GetDistance();
}

void Navigation::CoordinatePosition() {
    double averageInches = (Navigation::GetInchesTravelled().first + Navigation::GetInchesTravelled().second) / 2;
    xPosition +=  averageInches * sin(-robotAngleDifference);
    yPosition += averageInches * cos(-robotAngleDifference);
}

std::pair<double, double> Navigation::GetCoordinatePosition() {
    return std::make_pair(xPosition, yPosition);
}
