/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

////TODO: add piston movements to relevant methods

#include "subsystems/Intake.h"
#include "RobotContainer.h"
#include <iostream>

using StorageState = Intake::StorageState;

Intake::Intake() {
    InitMotorControllers();
    InitBallPositionSensors();
    SetInvertedFollower();

    //id and channel correct?
    intakePiston.reset(new frc::Solenoid(Constants::PCMCanBusID, 2));

}

void Intake::InitMotorControllers() {
    intakeTalon = std::make_shared<WPI_TalonSRX>(Constants::MotorIDs::intake);

    //check that these are brushless still
    primaryConveyorSpark = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::conveyor1, rev::CANSparkMax::MotorType::kBrushless);
    followerConveyorSpark = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::conveyor2, rev::CANSparkMax::MotorType::kBrushless);

    intakeTalon->ConfigPeakCurrentLimit(5);
}

void Intake::InitBallPositionSensors() {
    ballPosition = {
        new frc::DigitalInput(Constants::DigitalPort::ballPort0),
        new frc::DigitalInput(Constants::DigitalPort::ballPort1),
        new frc::DigitalInput(Constants::DigitalPort::ballPort2),
        new frc::DigitalInput(Constants::DigitalPort::ballPort3),
        new frc::DigitalInput(Constants::DigitalPort::ballPort4),
        new frc::DigitalInput(Constants::DigitalPort::ballPort5)
    };
}

//check direction of the second motor is still oposite
void Intake::SetInvertedFollower() {
    followerConveyorSpark->Follow(*primaryConveyorSpark, true);
}

void Intake::Periodic() {

    //Outputs position states to driver station
    InventoryPowerCells();
    for(int i=0; i<6; i++) {
        if (GetInventory(i) == StorageState::PRESENT) {
           std::cout << "Position " << i <<  " full\n";
        }
        else {
           std::cout << "Position " << i <<  " empty\n";
        }
    }
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
    intakeTalon->Set(0);
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

void Intake::NewRunConveyer(double speed) {
    primaryConveyorSpark->Set(speed);
}

double Intake::GetConveyerSpeed() {
    sparkSpeed = primaryConveyorSpark->Get();
    return sparkSpeed;
}

bool Intake::TrevinIntake() {
    bool stop;
    if (GetInventory(5) == StorageState::PRESENT) {
        StopConveyor();
        Stop();
        stop = true;
    }
    if (GetInventory(4) == StorageState::PRESENT) {
        fourHasBeenTripped = true;
    }
    if (GetInventory(0) == StorageState::PRESENT) {
        zeroHasBeenTripped = true;
        Stop();
        if (fourHasBeenTripped) {
            NewRunConveyer(Constants::Intake::slow);
        }
        else {
            NewRunConveyer();
        }
    }
    else if (GetInventory(0) == StorageState::EMPTY && zeroHasBeenTripped) {
        StopConveyor();
        stop = true;
    }
    return stop;
}

bool Intake::NewTrevinIntake() {
    bool stop;
    if (GetInventory(5) == StorageState::PRESENT || (GetInventory(0) == StorageState::EMPTY && zeroHasBeenTripped)) {
        std::cout << "Stopping Conveyers";
        StopConveyor();
        stop = true;
    }
    if (GetInventory(5) == StorageState::PRESENT || GetInventory(0) == StorageState::PRESENT) {
        Stop();
        std::cout << "Stopping Wheels";
    }
    else {
        std::cout << "Running Wheels";
        intakeTalon->Set(0.6);
    }
    if (GetInventory(0) == StorageState::PRESENT && GetInventory(4) == StorageState::PRESENT) {
        std::cout << "Running Slow";
        NewRunConveyer(Constants::Intake::slow);
    }
    else if (GetInventory(0) == StorageState::PRESENT) {
        std::cout << "Running Conveyers";
        NewRunConveyer();
    }
    return stop;
}

////TODO: Set Convey to reverse for perhaps 0.5 seconds or 10 loop cycles.
void Intake::StopConveyor() {
    primaryConveyorSpark->Set(0);
}

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
    for (int pos=0; pos<6; pos++) {
        if (GetInventory(pos) == Intake::StorageState::PRESENT)
            return false;
    }
    return true;
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

void Intake::IntakeOut() {
    intakePiston->Set(shiftOut); 
}

void Intake::IntakeIn() {
    intakePiston->Set(shiftIn);
}