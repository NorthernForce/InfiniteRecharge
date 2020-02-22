/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

Climber::Climber() {
    leftArmSpark.reset(new rev::CANSparkMax(Constants::Climber::leftArmMotor, rev::CANSparkMax::MotorType::kBrushless));
    rightArmSpark.reset(new rev::CANSparkMax(Constants::Climber::rightArmMotor, rev::CANSparkMax::MotorType::kBrushless));
    
    SetInvertedFollowers(); ////TODO: determine if arm sparks are inverted/where they are
}

void Climber::SetInvertedFollowers() {
    rightArmSpark->Follow(*leftArmSpark, true);
}

// This method will be called once per scheduler run
void Climber::Periodic() {}

void Climber::Lifter(double speed) {
    leftArmSpark->Set(speed);
}


