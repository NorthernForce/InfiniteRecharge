/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"


Intake::Intake() {
    intakeSpark.reset(new rev::CANSparkMax(Constants::Intake::intakeMotor, rev::CANSparkMax::MotorType::kBrushless));
    armSpark.reset(new rev::CANSparkMax(Constants::Intake::armMotor, rev::CANSparkMax::MotorType::kBrushless));
}

// This method will be called once per scheduler run
void Intake::Periodic() {}


void Intake::TakeIn() {
    intakeSpark->Set(.5);
}

void Intake::PushOut() {
    intakeSpark->Set(-.5);
}

void Intake::Stop() {
    intakeSpark->Set(0);
}

bool Intake::ArmUp() {
    if (armSpark->GetEncoder().SetPosition(-1.666667) == rev::CANError::kOk)  {     ////TODO: figure out if you want this to be negative or not
        armState = Constants::Intake::armIsUp;
        return true;
    }
    else {
        return false;
    }
}

bool Intake::ArmDown() {
    if (armSpark->GetEncoder().SetPosition(1.666667) == rev::CANError::kOk)  {   ////TODO: figure out if you want this to be negative or not
        armState = Constants::Intake::armIsDown;
        return true;
    }
    else {
        return false;
    }
}

bool Intake::ArmState() {
    return armState;
}
