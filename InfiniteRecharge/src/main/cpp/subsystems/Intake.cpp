/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"
#include "RobotContainer.h"
#include <iostream>

using ArmState = Intake::ArmState;
using StorageState = Intake::StorageState;

Intake::Intake() {
    InitMotorControllers();
    InitBallPositionSensors();
    SetInvertedFollower();
    currentArmState = ArmState::armIsUp;

}

void Intake::InitMotorControllers() {
    intakeTalon.reset(new WPI_TalonSRX(Constants::MotorIDs::intake));
    armSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intakeArm, rev::CANSparkMax::MotorType::kBrushless));
    armSpark->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    armSpark->SetSmartCurrentLimit(40);

    primaryConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor1, rev::CANSparkMax::MotorType::kBrushless));
    followerConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor2, rev::CANSparkMax::MotorType::kBrushless));

    intakeTalon->ConfigPeakCurrentLimit(5);
}

void Intake::InitBallPositionSensors() {
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort0));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort1));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort2));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort3));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort4));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort5));
}

void Intake::SetInvertedFollower() {
    followerConveyorSpark->Follow(*primaryConveyorSpark, true);
}

void Intake::Periodic() {
    InventoryPowerCells();
    for(int i=0; i<6; i++) {
        if (GetInventory(i) == StorageState::PRESENT) {
            //std::cout << "Position " << i <<  " full\n";
    }
        else {
            //std::cout << "Position " << i <<  " empty\n";
        }
   }
}

void Intake::TakeInPowerCell() {
    intakeTalon->Set(0.5);
}

void Intake::PushOutPowerCell() {
    intakeTalon->Set(0.5);
}

void Intake::Stop() {
    intakeTalon->Set(0);
}

void Intake::SetArmUp() {
    double tolerance = 3;
    if (currentArmState == ArmState::armIsDown) {
        armSpark->Set(-0.8);
        double armEncoderPos = armSpark->GetEncoder().GetPosition();
        if (abs(armEncoderPos) + tolerance >= 49 && abs(armEncoderPos) + tolerance > 0)
            currentArmState = ArmState::armIsUp;
        else
            currentArmState = ArmState::armIsDown;
        armSpark->Set(0);
    }
}

void Intake::SetArmDown() {
    double tolerance = 3;
    armSpark->Set(0.5);
    if (currentArmState == ArmState::armIsUp) {
        if (abs(armSpark->GetEncoder().GetPosition()) + tolerance >= 0) {
            currentArmState = ArmState::armIsDown;
            armSpark->GetEncoder().SetPosition(0);
            armSpark->Set(0);
        }
        else
            currentArmState = ArmState::armIsUp;
    }
}

void Intake::SetArm(double speed) {
    armSpark->Set(speed);
    std::cout << GetArmPosition() << '\n';
}

double Intake::GetArmPosition() {
    return armSpark->GetEncoder().GetPosition();
}

ArmState Intake::GetArmState() {
    return currentArmState;
}

void Intake::RunConveyor() {
    primaryConveyorSpark->Set(-0.4);
}

void Intake::StopConveyor() {
    primaryConveyorSpark->Set(0);
}

void Intake::InventoryPowerCells() {
    for(int pos=0; pos<6; pos++) {
        if (ballPosition[pos]->Get() == ballDetected)
            powerCellPosition[pos] = StorageState::PRESENT;
        else
            powerCellPosition[pos] = StorageState::EMPTY;
    }
}

//Returns a "StorageState" indicating whether there is a Power Cell at the Given (integer) Conveyor Storage Location 
StorageState Intake::GetInventory(int position) {
    return powerCellPosition[position];
}

//Return the First Position in the Conveyor Storage that is empty (no PC).
int Intake::GetFirstEmptyPosition() {
    int position = noEmptyPositionFound;
    for (int i = 1; i < 6; i++) {
        if (Intake::GetInventory(i) == StorageState::EMPTY) {
            position = i;
            break;
        }
    }
    return position;
}

int Intake::LowestFullPosition() {
    int position = noFullPositionFound;
    for (int i = 1; i < 6; i++) {
        if (Intake::GetInventory(i) == StorageState::EMPTY) {
            continue;
        }
        position = i;
    }
    return position;
}