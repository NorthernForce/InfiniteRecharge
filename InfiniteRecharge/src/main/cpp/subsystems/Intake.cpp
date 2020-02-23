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

void Intake::TakeIn() {
    intakeSpark->Set(0.5);
}

void Intake::PushOut() {
    intakeSpark->Set(-0.5);
}

void Intake::Stop() {
    intakeSpark->Set(0);
}

void Intake::ArmUp() {
    if (armSpark->GetEncoder().SetPosition(-1.666667) == rev::CANError::kOk)  {     ////TODO: figure out if you want this to be negative or not
        currentArmState = ArmState::armIsUp;
    }
}

void Intake::ArmDown() {
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
    for (int position = 0; position < 6; position++) {
        switch (position) {
            case 0: if (ballPosition0->Get() == ballDetected) {
                        powerCellPosition[position0] = StorageState::PRESENT;
                    }
                    else {
                        powerCellPosition[position0] = StorageState::EMPTY;
                    }
                    break;
            case 1: if (ballPosition1->Get() == ballDetected) {
                        powerCellPosition[position1] = StorageState::PRESENT;
                    }
                    else {
                        powerCellPosition[position1] = StorageState::EMPTY;
                    }
                    break;
            case 2: if (ballPosition2->Get() == ballDetected) {
                        powerCellPosition[position2] = StorageState::PRESENT;
                    }
                    else {
                        powerCellPosition[position2] = StorageState::EMPTY;
                    }
                    break;
            case 3: if (ballPosition3->Get() == ballDetected) {
                        powerCellPosition[position3] = StorageState::PRESENT;
                    }
                    else {
                        powerCellPosition[position3] = StorageState::EMPTY;
                    }
                    break;
            case 4: if (ballPosition4->Get() == ballDetected) {
                        powerCellPosition[position4] = StorageState::PRESENT;
                    }
                    else {
                        powerCellPosition[position4] = StorageState::EMPTY;
                    }
                    break;
            case 5: if (ballPosition5->Get() == ballDetected) {
                        powerCellPosition[position5] = StorageState::PRESENT;
                    }
                    else {
                        powerCellPosition[position5] = StorageState::EMPTY;
                    }
                    break;
        }
    }
}
StorageState Intake::GetInventory(int position) {
    return powerCellPosition[position];
}

int Intake::FirstEmptyPosition() {
    int position = noEmptyPositionFound;
    for (int i = 1; i < 6; i++) {
        if (Intake::GetInventory(i) == StorageState::PRESENT) {
            continue;
        }
        position = i;
    }
    return position;
}