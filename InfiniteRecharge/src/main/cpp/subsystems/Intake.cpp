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
    armSpark->SetSmartCurrentLimit(60);

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

    // Outputs position states to driver station
    InventoryPowerCells();
    // for(int i=0; i<6; i++) {
    //     if (GetInventory(i) == StorageState::PRESENT) {
    //        std::cout << "Position " << i <<  " full\n";
    //     }
    //     else {
    //        std::cout << "Position " << i <<  " empty\n";
    //     }
    // }
}

void Intake::ResetZHBT() {
    zeroHasBeenTripped = false;
}

void Intake::TrevinRunConveyer(double speed) {
    primaryConveyorSpark->Set(speed);
}

bool Intake::TrevinIntakeDebug() {
    bool stop = false;

    std::cout << "Zero Has been triggered: " << zeroHasBeenTripped << "\n";
    std::cout << "Stopping: " << stop << "\n";
    std::cout << "Inventory 5 Full: "<< (GetInventory(5) == StorageState::PRESENT) << "\n";

    if ((GetInventory(2) == StorageState::PRESENT) && (GetInventory(1) == StorageState::EMPTY) && (GetInventory(2) == StorageState::EMPTY)) {
        TrevinRunConveyer(0 - Constants::Intake::normal);
    }
    else {
        if ((GetInventory(5) == StorageState::PRESENT) || ((GetInventory(0) == StorageState::EMPTY) && zeroHasBeenTripped)) {
            std::cout << "Setting Stop to 1\n";
            TrevinRunConveyer(0);
            stop = true;
        }
        if ((GetInventory(5) == StorageState::PRESENT) || (GetInventory(0) == StorageState::PRESENT)) {
            intakeTalon->Set(0);
            std::cout << "Stopping Wheels\n";
        }
        else {
            std::cout << "Running Wheels\n";
            intakeTalon->Set(0.6);
        }
        if ((GetInventory(0) == StorageState::PRESENT) && (GetInventory(4) == StorageState::PRESENT)) {
            std::cout << "Running Slow\n";
            TrevinRunConveyer(Constants::Intake::slow);
            zeroHasBeenTripped = true;
        }
        else if (GetInventory(0) == StorageState::PRESENT) {
            std::cout << "Running Conveyers\n";
            TrevinRunConveyer();
            zeroHasBeenTripped = true;
        }
        if (zeroHasBeenTripped == false) {
            std::cout << "Waiting for ball\n";
        }
    }
    return stop;
}

////TODO: Update this to match Debug's code

bool Intake::TrevinIntakeCompact() {
    bool stop = false;
    if (GetInventory(5) == StorageState::PRESENT) {
        StopConveyor();
        Stop();
        stop = true;
    }
    if (GetInventory(0) == StorageState::PRESENT) {
        zeroHasBeenTripped = true;
        Stop();
        if (GetInventory(4) == StorageState::PRESENT) {
            TrevinRunConveyer(Constants::Intake::slow);
        }
        else {
            TrevinRunConveyer();
        }
    }
    else if ((GetInventory(0) == StorageState::EMPTY) && zeroHasBeenTripped) {
        StopConveyor();
        stop = true;
    }
    else {
        intakeTalon->Set(0.6);
    }
    return stop;
}


//Methods not used


//cycles through positions to get storage states
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

bool Intake::IsConveyorEmpty() {
    int emptyCounter = 0;
    bool isEmpty;
    for (int pos=0; pos<6; pos++) {
        if (GetInventory(pos) == Intake::StorageState::EMPTY)
            emptyCounter++;
    if (emptyCounter == 6)
        isEmpty = true;
    }
    return isEmpty;
}

void Intake::TakeInPowerCell() {
    intakeTalon->Set(0.6);
}

void Intake::SetIntakeSpeed(double speed) {
    intakeTalon->Set(speed);
}

void Intake::PushOutPowerCell() {
    intakeTalon->Set(-0.5);
}

//power cell counting might not be working
int Intake::GetPowerCellCount() {
    return powerCellCount;
}

void Intake::Stop() {
    intakeTalon->Set(0.0);
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

void Intake::StopConveyor() {
    primaryConveyorSpark->Set(0.0);
}

////TODO: Set Camera to low position before the arm is commanded
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

//runs arm motors regardless of arm state
////TODO: Block until Camera is safe
void Intake::SetArm(double speed) {
    armSpark->Set(speed);
    std::cout << "Arm Position" << GetArmPosition() << '\n';
}

double Intake::GetArmPosition() {
    return armSpark->GetEncoder().GetPosition();
}

ArmState Intake::GetArmState() {
    return currentArmState;
}

void Intake::RunConveyor() {
    //runs conveyor at faster speeds until position 4 or 5  is reached
    if (GetInventory(4) == StorageState::PRESENT || GetInventory(5) == StorageState::PRESENT) {
        primaryConveyorSpark->Set(-0.3);
    }
    else {
        primaryConveyorSpark->Set(-0.50);
    }
}

void Intake::ConveyorSetSpeed(double speed) {
    // runs conveyor faster until position 4 is full
    if (GetInventory(4) == StorageState::PRESENT || GetInventory(5) == StorageState::PRESENT) {
        primaryConveyorSpark->Set(speed);
    }
    else {
        //increases speed based on whether conveyor is moving forward or backward
        if (speed < 0) {
            primaryConveyorSpark->Set(speed - 0.15);
        }
        else {
            primaryConveyorSpark->Set(speed + 0.15);
        }
    }
}

double Intake::GetConveyerSpeed() {
    sparkSpeed = primaryConveyorSpark->Get();
    return sparkSpeed;
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