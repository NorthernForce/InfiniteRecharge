/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "RobotContainer.h"

AutoDrive::AutoDrive(double inches, double leftSpeed, double rightSpeed)
 : inchesToTravel(inches), leftMotorSpeed(leftSpeed), rightMotorSpeed(rightSpeed) {
    AddRequirements(RobotContainer::drivetrain.get());
}

// Use this only in autonomous or when calling from another command
void AutoDrive::SetDist(double inches) {
    inchesToTravel = inches;
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
    startDist = RobotContainer::drivetrain->GetAvgEncoderRotations();
    encoderToTravelTo = startDist + inchesToTravel * Constants::Shifting::highMultiplier;
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
    std::cout << "Autonomous running?\n";
    RobotContainer::drivetrain->DriveUsingSpeeds(leftMotorSpeed, rightMotorSpeed);
    encoderCurrent = RobotContainer::drivetrain->GetAvgEncoderRotations();
}

// Called once the command ends or is interrupted.
void AutoDrive::End(bool interrupted) {
    RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
}

// Returns true when the command should end.
bool AutoDrive::IsFinished() {
    if (abs(encoderToTravelTo) < abs(encoderCurrent))
        return true;
    else
        return false;
}