/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "Constants.h"

Drivetrain::Drivetrain() {    
    leftPrimarySpark.reset(new rev::CANSparkMax(Constants::MotorIDs::driveLeftPrimary, rev::CANSparkMax::MotorType::kBrushless));
    leftFollowerSpark1.reset(new rev::CANSparkMax(Constants::MotorIDs::driveLeftFollower1, rev::CANSparkMax::MotorType::kBrushless));
    leftFollowerSpark2.reset(new rev::CANSparkMax(Constants::MotorIDs::driveLeftFollower2, rev::CANSparkMax::MotorType::kBrushless));
    rightPrimarySpark.reset(new rev::CANSparkMax(Constants::MotorIDs::driveRightPrimary, rev::CANSparkMax::MotorType::kBrushless));
    rightFollowerSpark1.reset(new rev::CANSparkMax(Constants::MotorIDs::driveRightFollower1, rev::CANSparkMax::MotorType::kBrushless));
    rightFollowerSpark2.reset(new rev::CANSparkMax(Constants::MotorIDs::driveRightFollower2, rev::CANSparkMax::MotorType::kBrushless));
////Execute Methods to set up Motor Controllers (Followers, Ramping Rates, and Inverted Motors)
    SetInvertedFollowers();
    ConfigureAllControllers();

    robotDrive.reset(new frc::DifferentialDrive(*leftPrimarySpark, *rightPrimarySpark));
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
void Drivetrain::Periodic() {
    std::cout << "Encoder Pos:" << leftPrimarySpark->GetEncoder().GetPosition() << "\n";
}

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

std::pair<double, double> Drivetrain::GetEncoderRotations() {
    double leftSideRotations = leftPrimarySpark->GetEncoder().GetPosition() * -1;
    double rightSideRotations = rightPrimarySpark->GetEncoder().GetPosition();
    return std::make_pair(leftSideRotations, rightSideRotations);
}

void Drivetrain::SimpleDriveWithEncoder(double desiredEncoder) {
    if(leftPrimarySpark->GetEncoder().GetPosition() <= desiredEncoder) {
        leftPrimarySpark->Set(0.5);
        rightPrimarySpark->Set(0.5);
    }
}

void Drivetrain::SetEncoderPosition(double position) {
    leftPrimarySpark->GetEncoder().SetPosition(position);
    rightPrimarySpark->GetEncoder().SetPosition(position);
}

void Drivetrain::SimpleTurnToAngle(double limelightOffset) {
    if (limelightOffset < 0) {
        rightPrimarySpark->Set(0.6);
    } else if (limelightOffset > 0) {
        leftPrimarySpark->Set(-0.6);
    }
}