/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"

using ArmState = Intake::ArmState;

Intake::Intake() {
    intakeSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intake, rev::CANSparkMax::MotorType::kBrushless));
    armSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intakeArm, rev::CANSparkMax::MotorType::kBrushless));

    primaryConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor1, rev::CANSparkMax::MotorType::kBrushless));
    followerConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor2, rev::CANSparkMax::MotorType::kBrushless));

    ballPosition1.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort1));
    ballPosition2.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort2));
    ballPosition3.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort3));
    ballPosition4.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort4));
    ballPosition5.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort5));
}

void Intake::SetFollowers() {
    followerConveyorSpark->Follow(*primaryConveyorSpark, true);
}
void Intake::Periodic() {}

void Intake::TakeIn() {
    intakeSpark->Set(0.5);
}

void Intake::PushOut() {
    intakeSpark->Set(-0.5);
}

void Intake::Stop() {
    intakeSpark->Set(0);
}

bool Intake::ArmUp() {
    if (armSpark->GetEncoder().SetPosition(-1.666667) == rev::CANError::kOk)  {     ////TODO: figure out if you want this to be negative or not
        currentArmState = ArmState::armIsUp;
        return true;
    }
    else
        return false;
}

bool Intake::ArmDown() {
    if (armSpark->GetEncoder().SetPosition(1.666667) == rev::CANError::kOk)  {   ////TODO: figure out if you want this to be negative or not
        currentArmState = ArmState::armIsDown;
        return true;
    }
    else
        return false;
}

ArmState Intake::GetArmState() {
    return currentArmState;
}

void Intake::RunConveyor() {
    primaryConveyorSpark->Set(0.5);
}

void Intake::StopConveyor() {
    primaryConveyorSpark->Set(0);
}