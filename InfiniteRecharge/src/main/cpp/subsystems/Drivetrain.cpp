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

    robotDrive.reset(new frc::DifferentialDrive(*leftPrimarySpark, *rightPrimarySpark));

////Execute Methods to set up Motor Controllers (Followers, Ramping Rates, and Inverted Motors)
    SetFollowers();
    SetRamp();
    InvertFollowers();
}

void Drivetrain::SetFollowers() {
    leftFollowerSpark1->Follow(*leftPrimarySpark);
    leftFollowerSpark2->Follow(*leftPrimarySpark);
    rightFollowerSpark1->Follow(*rightPrimarySpark);
    rightFollowerSpark2->Follow(*rightPrimarySpark);
}

void Drivetrain::SetRamp() {
    leftPrimarySpark->SetClosedLoopRampRate(0.2);
    rightPrimarySpark->SetClosedLoopRampRate(0.2);
}

void Drivetrain::InvertFollowers() {
    leftFollowerSpark1->SetInverted(true);
    rightFollowerSpark1->SetInverted(true);
    leftFollowerSpark2->SetInverted(true);
    rightFollowerSpark2->SetInverted(true);
}

void Drivetrain::OutputCurrents() {
    std::cerr << "LP: " << leftPrimarySpark->GetOutputCurrent() << '\n';
    std::cerr << "RP: " << rightPrimarySpark->GetOutputCurrent() << '\n';
    std::cerr << "LF1: " << leftFollowerSpark1->GetOutputCurrent() << '\n';
    std::cerr << "RF1: " << rightFollowerSpark1->GetOutputCurrent() << '\n';
    std::cerr << "LF2: " << leftFollowerSpark2->GetOutputCurrent() << '\n';
    std::cerr << "RF2: " << rightFollowerSpark2->GetOutputCurrent() << '\n';
}

void Drivetrain::Drive(double speed, double rotation) {
    robotDrive->ArcadeDrive(speed, rotation);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    OutputCurrents();
}