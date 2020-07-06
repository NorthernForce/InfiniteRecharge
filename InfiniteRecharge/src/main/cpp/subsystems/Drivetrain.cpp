/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <RobotContainer.h>

Drivetrain::Drivetrain() {
    leftPrimarySpark = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveLeftPrimary, rev::CANSparkMax::MotorType::kBrushless);
    leftFollowerSpark1 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveLeftFollower1, rev::CANSparkMax::MotorType::kBrushless);
    leftFollowerSpark2 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveLeftFollower2, rev::CANSparkMax::MotorType::kBrushless);
    rightPrimarySpark = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveRightPrimary, rev::CANSparkMax::MotorType::kBrushless);
    rightFollowerSpark1 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveRightFollower1, rev::CANSparkMax::MotorType::kBrushless);
    rightFollowerSpark2 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveRightFollower2, rev::CANSparkMax::MotorType::kBrushless);

////Execute Methods to set up Motor Controllers (Followers, Ramping Rates, and Inverted Motors)
    SetInvertedFollowers();
    ConfigureAllControllers();

    robotDrive = std::make_shared<frc::DifferentialDrive>(*leftPrimarySpark, *rightPrimarySpark);
}

void Drivetrain::SetInvertedFollowers() {
    leftFollowerSpark1->Follow(*leftPrimarySpark, true);
    leftFollowerSpark2->Follow(*leftPrimarySpark, true);
    rightFollowerSpark1->Follow(*rightPrimarySpark, true);
    rightFollowerSpark2->Follow(*rightPrimarySpark, true);
}

void Drivetrain::ConfigureAllControllers() {
    ConfigureController(*leftPrimarySpark);
    ConfigureController(*leftFollowerSpark1);
    ConfigureController(*leftFollowerSpark2);
    ConfigureController(*rightPrimarySpark);
    ConfigureController(*rightFollowerSpark1);
    ConfigureController(*rightFollowerSpark2);
}

void Drivetrain::Drive(double speed, double rotation) {
    robotDrive->ArcadeDrive(speed, rotation * 0.85);
}

void Drivetrain::DriveUsingSpeeds(double leftSpeed, double rightSpeed) {
    leftPrimarySpark->Set(-leftSpeed);
    rightPrimarySpark->Set(rightSpeed);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {}

// Sets each Spark motor controller with current limits, a speed ramp, and brake
void Drivetrain::ConfigureController(rev::CANSparkMax& controller) {
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  if(!controller.IsFollower())
  {
    controller.SetClosedLoopRampRate(rampRate);
    controller.SetOpenLoopRampRate(rampRate);
  }
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

double Drivetrain::GetLeftRPM() {
    return leftPrimarySpark->GetEncoder().GetVelocity() * -1;
}

double Drivetrain::GetRightRPM() {
    return rightPrimarySpark->GetEncoder().GetVelocity() * -1;
}

double Drivetrain::GetAvgRPM() {
    return ((GetLeftRPM() + GetRightRPM()) / 2);
}

std::pair<double, double> Drivetrain::GetEncoderRotations() {
    double leftSideRotations = leftPrimarySpark->GetEncoder().GetPosition();
    double rightSideRotations = rightPrimarySpark->GetEncoder().GetPosition() * -1;
    return std::make_pair(leftSideRotations, rightSideRotations);
}

double Drivetrain::GetAvgEncoderRotations() {
    double left = GetEncoderRotations().first;
    double right = GetEncoderRotations().second;
    double avgRots = (left + right) / 2;
    return avgRots;
}

// This does not work as intended, use autodrive command instead
void Drivetrain::SimpleDriveWithEncoder(double desiredEncoder) {
    if ((leftPrimarySpark->GetEncoder().GetPosition() && rightPrimarySpark->GetEncoder().GetPosition()) <= desiredEncoder) {
        leftPrimarySpark->Set(0.3);
        rightPrimarySpark->Set(0.3);
    }
}

void Drivetrain::SetEncoderPosition(double position) {
    leftPrimarySpark->GetEncoder().SetPosition(position);
    rightPrimarySpark->GetEncoder().SetPosition(position);
}

int Drivetrain::GetSpeedInInchesPerSecond() {
    prevEncoder = currentEncoder;
    currentEncoder = GetAvgEncoderRotations();
    double changeInPosition = abs(currentEncoder - prevEncoder);

    int convertToInchesMultiplier;
    if (RobotContainer::driveShifter->GetGear() == DriveShifter::Gear::Low)
        convertToInchesMultiplier = Constants::lowDriveMultiplier; 
    else
        convertToInchesMultiplier = Constants::highDriveMultiplier;
        
    return convertToInchesMultiplier * changeInPosition * loopCyclesInOneSecond;
}