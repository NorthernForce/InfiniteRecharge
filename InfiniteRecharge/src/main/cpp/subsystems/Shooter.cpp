/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "Constants.h"
#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>

Shooter::Shooter() {
    shooterTalon = std::make_shared<WPI_TalonFX>(new Constants::MotorIDs::shooter);
    shooterShifter.reset(new frc::Solenoid(Constants::PCMCanBusID, 1));
    timer.reset(new frc::Timer());

    // pidController->SetP(p);
    // pidController->SetI(i);
    // pidController->SetD(d);
    // pidController->SetFF(ff); 
    // pidController->SetIMaxAccum(maxI);
    // pidController->SetOutputRange(minOutput, maxOutput);

    ConfigureSpark();
    frc::SmartDashboard::PutNumber("Shooter target RPM: ", targetRPM);
    // frc::SmartDashboard::PutNumber("Shooter P: ", p);
    // frc::SmartDashboard::PutNumber("Shooter I: ", i);
    // frc::SmartDashboard::PutNumber("Shooter D: ", d);
    // frc::SmartDashboard::PutNumber("Shooter FF: ", ff);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    targetRPM = frc::SmartDashboard::GetNumber("Shooter target RPM: ", targetRPM);
    // p = frc::SmartDashboard::GetNumber("Shooter P: ", p);
    // i = frc::SmartDashboard::GetNumber("Shooter I: ", i);
    // d = frc::SmartDashboard::GetNumber("Shooter D: ", d);
    // ff = frc::SmartDashboard::GetNumber("Shooter FF: ", ff);

    // if (pidController->GetP() != p)
    //     pidController->SetP(p);
    // if (pidController->GetI() != i)
    //     pidController->SetI(i);
    // if (pidController->GetD() != d)
    //     pidController->SetD(d);
    // if (pidController->GetIMaxAccum() != maxI)
    //     pidController->SetIMaxAccum(maxI);
    // if (pidController->GetOutputMin() != minOutput || pidController->GetOutputMax() != maxOutput)
    //     pidController->SetOutputRange(minOutput, maxOutput);   
}

void Shooter::ConfigureSpark() {
    auto &controller = *shooterTalon; //nice
    controller.ConfigSupplyCurrentLimit(new ctre::phoenix::motorcontrol::SupplyCurrentLimitConfiguration(true, currentLimit))
    controller.ConfigStatorCurrentLimit(new ctre::phoenix::motorcontrol::StatorCurrentLimitConfiguration(true, secondaryCurrentLimit));
    controller.SetNeutralMode(ctre::pheonix::motorcontroll::NeutralMode::Coast);
}

void Shooter::IdleShooter() {
    // pidController->SetReference(targetRPM * idlePercentage, rev::ControlType::kVelocity);
}

void Shooter::Shoot() {
    // pidController->SetReference(targetRPM, rev::ControlType::kVelocity);
}

void Shooter::SetRawSpeed(double speed) {
    shooterTalon->Set(speed);
}

int Shooter::GetCurrentRPM() {
    return shooterTalon->getSensorCollection().getIntegratedSensorVelocity();
}

void Shooter::SetCurrentRPMTo(int rpm) {
    // pidController->SetReference(rpm, rev::ControlType::kVelocity);
}

int Shooter::GetTargetRPM() {
    return targetRPM;
}

void Shooter::SetTargetRPM(int rpm) {
    targetRPM = rpm;
}

int Shooter::GetError() {
    return abs(targetRPM - GetCurrentRPM());
}

void Shooter::ShooterUp() {
    shooterShifter->Set(shiftOn); 
}

void Shooter::ShooterDown() {
    shooterShifter->Set(shiftOff);
}