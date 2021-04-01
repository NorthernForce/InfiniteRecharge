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
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>

double Shooter::rampRate;

Shooter::Shooter() {
    shooterTalon = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::shooter);
    hoodTalon = std::make_unique<WPI_TalonSRX>(Constants::MotorIDs::hood);
    susanSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::susan, rev::CANSparkMax::MotorType::kBrushless);
    //pidController.reset(new rev::CANPIDController(shooterTalon->rev::CANSparkMax::GetPIDController()));
    shooterShifter = std::make_unique<frc::Solenoid>(Constants::PCMCanBusID, 1);
    timer = std::make_unique<frc::Timer>();
    sexyLimitSwitch = std::make_unique<frc::DigitalInput>(Constants::MotorIDs::susan);
    hoodLimitSwitch = std::make_unique<frc::DigitalInput>(Constants::MotorIDs::hood);

/*
    pidController->SetP(p);
    pidController->SetI(i);
    pidController->SetD(d);
    pidController->SetFF(ff); 
    pidController->SetIMaxAccum(maxI);
    pidController->SetOutputRange(minOutput, maxOutput);
    ConfigureSpark(.2);
    frc::SmartDashboard::PutNumber("Shooter target RPM: ", targetRPM);
    frc::SmartDashboard::PutNumber("Shooter P: ", p);
    frc::SmartDashboard::PutNumber("Shooter I: ", i);
    frc::SmartDashboard::PutNumber("Shooter D: ", d);
    frc::SmartDashboard::PutNumber("Shooter FF: ", ff);
    */
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    targetRPM = frc::SmartDashboard::GetNumber("Shooter target RPM: ", targetRPM);
    p = frc::SmartDashboard::GetNumber("Shooter P: ", p);
    i = frc::SmartDashboard::GetNumber("Shooter I: ", i);
    d = frc::SmartDashboard::GetNumber("Shooter D: ", d);
    ff = frc::SmartDashboard::GetNumber("Shooter FF: ", ff);

/*
    if (pidController->GetP() != p)
        pidController->SetP(p);
    if (pidController->GetI() != i)
        pidController->SetI(i);
    if (pidController->GetD() != d)
        pidController->SetD(d);
    if (pidController->GetIMaxAccum() != maxI)
        pidController->SetIMaxAccum(maxI);
    if (pidController->GetOutputMin() != minOutput || pidController->GetOutputMax() != maxOutput)
        pidController->SetOutputRange(minOutput, maxOutput);   
        */

    frc::SmartDashboard::PutBoolean("sexy", sexyLimitSwitch->Get());
    frc::SmartDashboard::PutBoolean("hood", hoodLimitSwitch->Get());
}

bool Shooter::GetLazySusanLimitSwitch() {
    return !sexyLimitSwitch->Get();
}

bool Shooter::GetHoodLimitSwitch() {
    return hoodLimitSwitch->Get();
}

void Shooter::ConfigureSpark(double ramp) {
    /*
    auto &controller = *shooterTalon; //nice
    rampRate = ramp;
    controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
    controller.SetSmartCurrentLimit(currentLimit);
    controller.SetClosedLoopRampRate(rampRate);
    controller.SetOpenLoopRampRate(rampRate);
    controller.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    */
}

void Shooter::IdleShooter() {
    /*
    pidController->SetReference(targetRPM * idlePercentage, rev::ControlType::kVelocity);
    */
}

void Shooter::Shoot() {
    /*
    pidController->SetReference(targetRPM, rev::ControlType::kVelocity);
    */
}

void Shooter::SetRawSpeed(double speed) {
    shooterTalon->Set(speed);
}

void Shooter::SetHoodSpeed(double speed){
    hoodTalon->Set(speed);
}

int Shooter::GetCurrentRPM() {
    return shooterTalon->GetSensorCollection().GetIntegratedSensorVelocity();
    /*
    return shooterTalon->GetActiveTrajectoryVelocity();
    */
}

void Shooter::SetCurrentRPMTo(int rpm) {
    /*
    pidController->SetReference(rpm, rev::ControlType::kVelocity);
    */
}

int Shooter::GetTargetRPM() {
    return targetRPM;
}

void Shooter::SetTargetRPM(int rpm) {
    targetRPM = rpm;
}

int Shooter::GetError() {
    return targetRPM - GetCurrentRPM();
}

void Shooter::ShooterUp() {
    shooterShifter->Set(shiftOn); 
}

void Shooter::ShooterDown() {
    shooterShifter->Set(shiftOff);
}

void Shooter::SetSusanSpeed(double speed) {
    if (IsSusanSpeedWithinLimits(speed))
        susanSpark->Set(speed);      
}

bool Shooter::IsSusanSpeedWithinLimits(double speed) {
    if (speed >= -1 || speed <= 1) {
        if (!GetLazySusanLimitSwitch()) {
            if (abs(GetLazySusanAngle()) <= 90)
                return true;
        }
    }
    return false;
}