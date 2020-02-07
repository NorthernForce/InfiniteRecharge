/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "Constants.h"

Drivetrain::Drivetrain() {    
    leftPrimarySpark.reset(new rev::CANSparkMax(Constants::Drivetrain::leftPrimary, rev::CANSparkMax::MotorType::kBrushless));
    leftFollowerSpark1.reset(new rev::CANSparkMax(Constants::Drivetrain::leftFollower1, rev::CANSparkMax::MotorType::kBrushless));
    leftFollowerSpark2.reset(new rev::CANSparkMax(Constants::Drivetrain::leftFollower2, rev::CANSparkMax::MotorType::kBrushless));
    rightPrimarySpark.reset(new rev::CANSparkMax(Constants::Drivetrain::rightPrimary, rev::CANSparkMax::MotorType::kBrushless));
    rightFollowerSpark1.reset(new rev::CANSparkMax(Constants::Drivetrain::rightFollower1, rev::CANSparkMax::MotorType::kBrushless));
    rightFollowerSpark2.reset(new rev::CANSparkMax(Constants::Drivetrain::rightFollower2, rev::CANSparkMax::MotorType::kBrushless));
////Execute Methods to set up Motor Controllers (Followers, Ramping Rates, and Inverted Motors)
    SetInvertedFollowers();
    SetupControllers();

    robotDrive.reset(new frc::DifferentialDrive(*leftPrimarySpark, *rightPrimarySpark));
}

void Drivetrain::SetInvertedFollowers() {
    leftFollowerSpark1->Follow(*leftPrimarySpark, true);
    leftFollowerSpark2->Follow(*leftPrimarySpark, true);
    rightFollowerSpark1->Follow(*rightPrimarySpark, true);
    rightFollowerSpark2->Follow(*rightPrimarySpark, true);
}

void Drivetrain::SetupControllers() {
    ConfigureController(*leftPrimarySpark);
    ConfigureController(*leftFollowerSpark1);
    ConfigureController(*leftFollowerSpark2);
    ConfigureController(*rightPrimarySpark);
    ConfigureController(*rightFollowerSpark1);
    ConfigureController(*rightFollowerSpark2);
}

void Drivetrain::Drive(double speed, double rotation) {
    robotDrive->ArcadeDrive(speed, rotation);
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
    return leftPrimarySpark->GetEncoder().GetVelocity();
}

double Drivetrain::GetRightRPM() {
    return rightPrimarySpark->GetEncoder().GetVelocity();
}