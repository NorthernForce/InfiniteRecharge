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
    ChangeInDistanceTravelled();
    TotalInchesTravelled();
    CoordinatePosition();
    // std::cout << "EncoderPos" << RobotContainer::drivetrain->GetEncoderRotations().first;
    smartdashCycles++;
    smartdashCycles = smartdashCycles % 20;
    if(!smartdashCycles) {
        frc::SmartDashboard::PutNumber("Left Inches", totalInchesTravelled.first);
        frc::SmartDashboard::PutNumber("Right Inches", totalInchesTravelled.second);
        frc::SmartDashboard::PutNumber("xPostition: ", xPosition);
        frc::SmartDashboard::PutNumber("yPosition: ", yPosition);
        frc::SmartDashboard::PutNumber("angleToFinal", AngleToPoint(12,0));
    }
}

//Calculates how far the robot has moved since the last call of the method in inches
void Navigation::ChangeInDistanceTravelled() {
    //Calculates left encoder rotations since last call
    double leftEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().first;
    double leftDistTravelled = leftEncoderPos - previousLeftEncoder;
    previousLeftEncoder = leftEncoderPos;
    //Calculates right encoder rotations since last call
    double rightEncoderPos = RobotContainer::drivetrain->GetEncoderRotations().second;
    double rightDistTravelled = rightEncoderPos - previousRightEncoder;
    previousRightEncoder = rightEncoderPos;

    //Converts encoder rotations into inches based off current gear
    if (RobotContainer::driveShifter->GetGear() == DriveShifter::Gear::High) {
        leftDistTravelled /= Constants::Shifting::highMultiplier;
        rightDistTravelled /= Constants::Shifting::highMultiplier;
    }
    else {
        leftDistTravelled /= Constants::Shifting::highMultiplier;
        rightDistTravelled /= Constants::Shifting::highMultiplier;
    }
    //Updates smartdashboard once every 20 cycles
    if (!smartdashCycles) {
        frc::SmartDashboard::PutNumber("Left Inches", leftDistTravelled);
        frc::SmartDashboard::PutNumber("Right Inches", rightDistTravelled);
    }
    changeInDistanceTravelled = std::make_pair(leftDistTravelled, rightDistTravelled);
}


void Navigation::TotalInchesTravelled() {
    totalInchesTravelled.first += changeInDistanceTravelled.first;
    totalInchesTravelled.second += changeInDistanceTravelled.second;
}

//Calculates coordinate position with sensors
void Navigation::ResetPosition() {
  xPosition = RobotContainer::aiComms->GetNumber(RobotContainer::aiComms->distanceToPcFromCam_label) * NavXScaling * abs(cos(robotAngleDifference));
  yPosition = RobotContainer::ultrasonic->GetDistance();
}

//Sets position to zero regardless of actual position
void Navigation::ZeroPosition() {
    xPosition = 0;
    yPosition = 0;
    //Called to update previous encoder pos
    ChangeInDistanceTravelled();
}

void Navigation::CoordinatePosition() {
    double averageInchesChange;
    //Combines wheel rotations into one measurement
    averageInchesChange = (changeInDistanceTravelled.first + changeInDistanceTravelled.second) / 2;

    //Adds the change in distance to the x and y coordinates
    xPosition -= averageInchesChange * std::cos(Constants::degreesToRadians * -robotCurrentAngle); // 0° & 180°
    yPosition -= averageInchesChange * std::sin(Constants::degreesToRadians * -robotCurrentAngle); //90° & 270°
    //Updates the smartdash once per 20 cycles
    if(!smartdashCycles) {
        frc::SmartDashboard::PutNumber("Nav Average inches: ", averageInchesChange);
    }
}

std::pair<double, double> Navigation::GetCoordinatePosition() {
    return std::make_pair(xPosition, yPosition);
}

double Navigation::AngleToPoint(double xPos, double yPos) {
    double angToPoint;
    double xChange = xPos - xPosition;
    double yChange = yPos - yPosition;

    if (xChange == 0) {
        angToPoint = 90 * (1 - 2 * (yChange > 0));
    }
    else {
        angToPoint = -(atan(yChange/xChange)) + ((1 - 2 * (int)(yChange > 0)) * 180 * (xChange < 0)) - RobotContainer::imu->GetRotation();
    }
    return angToPoint;
}