/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"

Climber::Climber() {
    armTalon.reset(new WPI_TalonSRX(Constants::Climber::leftArmMotor, rev::CANSparkMax::MotorType::kBrushless));
    
}

// This method will be called once per scheduler run
void Climber::Periodic() {}

void Climber::Lifter(double speed) {
    armSpark->Set(speed);
}


