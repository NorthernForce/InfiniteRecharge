/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"

using ArmState = Intake::ArmState;
using StorageState = Intake::StorageState;

Intake::Intake() {
    intakeSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intake, rev::CANSparkMax::MotorType::kBrushless));
    armSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::intakeArm, rev::CANSparkMax::MotorType::kBrushless));

    primaryConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor1, rev::CANSparkMax::MotorType::kBrushless));
    followerConveyorSpark.reset(new rev::CANSparkMax(Constants::MotorIDs::conveyor2, rev::CANSparkMax::MotorType::kBrushless));

    ballPosition0.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort0));
    ballPosition1.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort1));
    ballPosition2.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort2));
    ballPosition3.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort3));
    ballPosition4.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort4));
    ballPosition5.reset(new frc::DigitalInput(Constants::DigitalPort::ballPort5));
}

void Intake::SetFollowers() {
    followerConveyorSpark->Follow(*primaryConveyorSpark);
}
void Intake::Periodic() {}

void Intake::TakeInPowercell() {
    intakeSpark->Set(0.5);
}

void Intake::PushOutPowercell() {
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
    bool ball[6];
    ball[0] = ballPosition0->Get();
    ball[1] = ballPosition1->Get();
    ball[2] = ballPosition2->Get();
    ball[3] = ballPosition3->Get();
    ball[4] = ballPosition4->Get();
    ball[5] = ballPosition5->Get();
    for (int pos=0; pos<6; pos++) {
        if (ball[pos] == ballDetected)
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