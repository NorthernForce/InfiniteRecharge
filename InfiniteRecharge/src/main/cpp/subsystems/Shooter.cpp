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
    hoodSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::hood, rev::CANSparkMax::MotorType::kBrushed);
    susanSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::susan, rev::CANSparkMax::MotorType::kBrushless);
    //pidController.reset(new rev::CANPIDController(shooterTalon->rev::CANSparkMax::GetPIDController()));
    shooterShifter = std::make_unique<frc::Solenoid>(Constants::PCMCanBusID, 1);
    timer = std::make_unique<frc::Timer>();
    sexyLimitSwitch = std::make_unique<frc::DigitalInput>(Constants::DigitalPort::susanLimitSwitch);
    hoodLimitSwitch = std::make_unique<frc::DigitalInput>(Constants::MotorIDs::hood);

    hoodSpark->SetOpenLoopRampRate(0.5);
    ConfigureShooterTalon();
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    targetRPM = frc::SmartDashboard::GetNumber("Shooter target RPM: ", targetRPM);
    p = frc::SmartDashboard::GetNumber("Shooter P: ", p);
    i = frc::SmartDashboard::GetNumber("Shooter I: ", i);
    d = frc::SmartDashboard::GetNumber("Shooter D: ", d);
    ff = frc::SmartDashboard::GetNumber("Shooter FF: ", ff);

    UpdateLazySusanAngle();
    UpdateHoodAngle();

    frc::SmartDashboard::PutBoolean("sexy", sexyLimitSwitch->Get());
    frc::SmartDashboard::PutBoolean("hood", hoodLimitSwitch->Get());
    frc::SmartDashboard::PutNumber("susanAngle", GetLazySusanAngle());
    frc::SmartDashboard::PutNumber("hoodAngle", GetHoodAngle());
}

bool Shooter::GetLazySusanLimitSwitch() {
    return sexyLimitSwitch->Get();
}

bool Shooter::GetHoodLimitSwitch() {
    return hoodLimitSwitch->Get();
}

void Shooter::ConfigureShooterTalon(double ramp) {
    shooterTalon->ConfigFactoryDefault();
    shooterTalon->SetNeutralMode(NeutralMode::Coast);
    // shooterTalon->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, currentLimit, (currentLimit-5), 30));
    // shooterTalon->ConfigStatorCurrentLimit(StatorCurrentLimitConfiguration(true, secondaryCurrentLimit, (secondaryCurrentLimit-5), 30));
    
    /* Config neutral deadband to be the smallest possible */
    shooterTalon->ConfigNeutralDeadband(0.001);

    shooterTalon->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, pidLoopIdx, timeoutMs);
                                        
    shooterTalon->ConfigNominalOutputForward(0, timeoutMs);
    shooterTalon->ConfigNominalOutputReverse(0, timeoutMs);
    shooterTalon->ConfigPeakOutputForward(1, timeoutMs);
    shooterTalon->ConfigPeakOutputReverse(-1, timeoutMs);

    shooterTalon->Config_kF(pidLoopIdx, ff, timeoutMs);
    shooterTalon->Config_kP(pidLoopIdx, p, timeoutMs);
    shooterTalon->Config_kI(pidLoopIdx, i, timeoutMs);
    shooterTalon->Config_kD(pidLoopIdx, d, timeoutMs);

    shooterTalon->ConfigOpenloopRamp(5);
    shooterTalon->SetInverted(true);
}

void Shooter::IdleShooter() {}

void Shooter::Shoot() {
    SetCurrentRPMTo(targetRPM);
}

void Shooter::SetRawSpeed(double speed) {
    shooterTalon->Set(-speed);
}

void Shooter::SetHoodSpeed(double speed){
    hoodSpark->Set(speed);
}

int Shooter::GetCurrentRPM() {
    double velocity = -shooterTalon->GetSensorCollection().GetIntegratedSensorVelocity();
    int rpm = (velocity * msTorpm) / cpr;
    return rpm;
}

void Shooter::SetCurrentRPMTo(int rpm) {
    double velocity = (rpm * cpr) / msTorpm;
    std::cout << "velocity: " + std::to_string(velocity) + "\n";
    shooterTalon->Set(TalonFXControlMode::Velocity, velocity);
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
    // if (abs(lazySusanAngle) > 85)
        susanSpark->Set(speed);
}

void Shooter::UpdateLazySusanAngle() {
    double encoder;
    // if (GetLazySusanLimitSwitch())
    //     encoder = 0;
    // else
    encoder = susanSpark->GetEncoder().GetPosition();

    double shaftWheelCirc = (Constants::pi * 0.28125);
    int lazySusanCirc = (Constants::pi * 3.5);
    int gearRatio = 14; //14:1 motor:susan
    int degs = 360;
    
    lazySusanAngle = ((((encoder * shaftWheelCirc) / lazySusanCirc) / gearRatio) / degs) - limitSwitchAngOffset;
}

double Shooter::GetLazySusanAngle() {
    return lazySusanAngle;    
}

bool Shooter::IsSusanSpeedWithinLimits(double speed) {
    if (speed >= -1 || speed <= 1) {
        if (abs(GetLazySusanAngle()) <= limitSwitchAngOffset)
            return true;
    }
    return false;
}

double Shooter::GetHoodAngle() {
    return hoodAngle;
}

void Shooter::UpdateHoodAngle() {
    if (GetHoodLimitSwitch())
        hoodAngle = 0;
    else
        hoodAngle = hoodSpark->GetAnalog().GetVoltage(); ////TODO: convert potentiometer reading to angle
}