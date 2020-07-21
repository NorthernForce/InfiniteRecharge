/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* This is version 2020/7/20                                                  */
/*----------------------------------------------------------------------------*/

#include "subsystems/Navigation.h"
#include "RobotContainer.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>

#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

double Navigation::xPosition;
double Navigation::yPosition;

Navigation::Navigation() {}

////TODO: Need to calculate position
// This method will be called once per scheduler run
void Navigation::Periodic() {
    robotCurrentAngle = RobotContainer::imu->GetRotation();
    averageSpeedInRPM = (RobotContainer::drivetrain->GetLeftRPM() + RobotContainer::drivetrain->GetRightRPM() / 2);
    CoordinatePosition();
    // std::cout << "EncoderPos" << RobotContainer::drivetrain->GetEncoderRotations().first;
    smartdashCycles++;
    smartdashCycles = smartdashCycles % 20;
}

std::pair<double, double> Navigation::GetInchesTravelled() {
    double leftEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().first;
    double rightEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().second;

    if (RobotContainer::driveShifter->GetGear() == DriveShifter::Gear::High) {
        leftEncoderPos /= Constants::Shifting::highMultiplier;
        rightEncoderPos /= Constants::Shifting::highMultiplier;
    }
    else {
        leftEncoderPos /= Constants::Shifting::highMultiplier;
        rightEncoderPos /= Constants::Shifting::highMultiplier;
    }
    if (!smartdashCycles) {
        frc::SmartDashboard::PutNumber("Left Inches", leftEncoderPos);
        frc::SmartDashboard::PutNumber("Right Inches", rightEncoderPos);
    }
    return std::make_pair(leftEncoderPos, rightEncoderPos);
}

void Navigation::ResetPosition() {
  xPosition = RobotContainer::aiComms->GetNumber(RobotContainer::aiComms->distanceToPcFromCam_label) * NavXScaling * abs(cos(robotAngleDifference));
  yPosition = RobotContainer::ultrasonic->GetDistance();
}

void Navigation::ZeroPosition() {
    xPosition = 0;
    yPosition = 0;
}

// void Navigation::CoordinatePosition() {
//     double averageInches = (Navigation::GetInchesTravelled().first + Navigation::GetInchesTravelled().second) / 2;
//     frc::SmartDashboard::PutNumber("Nav Average inches: ", averageInches);
//     xPosition +=  averageInches * sin(robotCurrentAngle);
//     yPosition += averageInches * cos(robotCurrentAngle);
// }

void Navigation::CoordinatePosition() {
    //Combines wheel rotations into one measurement
    double averageInchesChange;
    averageInches = (Navigation::GetInchesTravelled().first + Navigation::GetInchesTravelled().second) / 2;
    averageInchesChange = averageInchesChange - averageInchesBuffer;
    averageInchesBuffer = averageInchesChange;

    //Adds the change in distance to the x and y coordinates
    xPosition += averageInchesChange * std::sin(Constants::degreesToRadians * robotCurrentAngle); //90° & 270°
    yPosition += averageInchesChange * std::cos(Constants::degreesToRadians * robotCurrentAngle);  // 0° & 180°
    if(!smartdashCycles) {
        frc::SmartDashboard::PutNumber("Nav Average inches: ", averageInches);
        frc::SmartDashboard::PutNumber("Average Inches buffer: ", averageInchesBuffer);
        frc::SmartDashboard::PutNumber("xPostition: ", xPosition);
        frc::SmartDashboard::PutNumber("yPosition: ", yPosition);
    }
}

std::pair<double, double> Navigation::GetCoordinatePosition() {
    return std::make_pair(xPosition, yPosition);
}
