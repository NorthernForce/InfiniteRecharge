/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"
#include "RobotContainer.h"

using ArmState = Intake::ArmState;
using StorageState = Intake::StorageState;

Intake::Intake() {
    InitSparks();
    InitBallPositionSensors();
    SetFollowers();
}

void Intake::InitSparks() {
    intakeSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intake, rev::CANSparkMax::MotorType::kBrushless));
    armSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intakeArm, rev::CANSparkMax::MotorType::kBrushless));

    primaryConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor1, rev::CANSparkMax::MotorType::kBrushless));
    followerConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor2, rev::CANSparkMax::MotorType::kBrushless));
}

void Intake::InitBallPositionSensors() {
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort0));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort1));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort2));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort3));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort4));
    ballPosition.push_back(new frc::DigitalInput(Constants::DigitalPort::ballPort5));
}

void Intake::SetFollowers() {
    followerConveyorSpark->Follow(*primaryConveyorSpark);
}
void Intake::Periodic() {
    RobotContainer::intake->InventoryPowerCells();
}

void Intake::TakeInPowerCell() {
    intakeSpark->Set(0.5);
}

void Intake::PushOutPowerCell() {
    intakeSpark->Set(-0.5);
}

void Intake::Stop() {
    intakeSpark->Set(0);
}

void Intake::SetArmUp() {
    if (armSpark->GetEncoder().SetPosition(-1.666667) == rev::CANError::kOk)  {     ////TODO: figure out if you want this to be negative or not
        currentArmState = ArmState::armIsUp;
    }
}

void Intake::SetArmDown() {
    if (armSpark->GetEncoder().SetPosition(1.666667) == rev::CANError::kOk)  {   ////TODO: figure out if you want this to be negative or not
        currentArmState = ArmState::armIsDown;
    }
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
        if (Intake::GetInventory(i) == StorageState::PRESENT) {
            continue;
        }
        position = i;
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