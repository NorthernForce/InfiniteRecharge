/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>

AutoDrive::AutoDrive(double inches, double leftSpeed, double rightSpeed)
 : leftMotorSpeed(leftSpeed), rightMotorSpeed(rightSpeed) {
    AddRequirements(RobotContainer::drivetrain.get());
    if (inches != 0)
        SetDist(inches);
}

// Use this only in autonomous or when calling from another command
void AutoDrive::SetDist(double inches) {
    inchesToTravel = inches;
}

double AutoDrive::GetDist() {
    return inchesToTravel;
}

// Use this only in autonomous or when calling from another command
void AutoDrive::SetSpeeds(double leftSpeed, double rightSpeed) {
    if (rightSpeed != leftSpeed)
        rightSpeed = leftSpeed;
    leftMotorSpeed = leftSpeed;
    rightMotorSpeed = rightSpeed;
}

// Called when the command is initially scheduled.
void AutoDrive::Initialize() {
    CheckForAndFixNegatives();
    startDist = -1 * RobotContainer::drivetrain->GetEncoderRotations().first;
    encoderToTravelTo = startDist + (inchesToTravel * Constants::Shifting::highMultiplier);
}

void AutoDrive::CheckForAndFixNegatives() {
    if (inchesToTravel < 0) {
        inchesToTravel *= -1;
        leftMotorSpeed *= -1;
        rightMotorSpeed *= -1;
    }
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
    RobotContainer::drivetrain->DriveUsingSpeeds(leftMotorSpeed, rightMotorSpeed);
    encoderCurrent = -1 * RobotContainer::drivetrain->GetEncoderRotations().first;
    frc::SmartDashboard::PutNumber("current encoder", encoderCurrent);
}

// Called once the command ends or is interrupted.
void AutoDrive::End(bool interrupted) {
    RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
}

bool AutoDrive::HasReachedTargetDistance() {
    if (encoderToTravelTo >= 0)
        return encoderCurrent >= encoderToTravelTo;
    else if (encoderToTravelTo < 0)
        return encoderCurrent <= encoderToTravelTo;
    else
        return false;
}

// Returns true when the command should end.
bool AutoDrive::IsFinished() {
    return HasReachedTargetDistance();
}