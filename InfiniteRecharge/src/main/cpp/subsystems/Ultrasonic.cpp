/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Ultrasonic.h"
#include <iostream>

//all digital stuff is commented out

Ultrasonic::Ultrasonic() {
    //ctrl.reset(new frc::DigitalOutput(Constants::Ultrasonic::digitalCtrlPort));
}

// This method will be called once per scheduler run
void Ultrasonic::Periodic() {
    if (ultrasonicOn) {
        distance = analogUltrasonic.GetValue() * ValueToInches;
        std::cout << distance << "\n";
    }

    else {
        distance = 0;
    }
}

double Ultrasonic::GetDistance() {
    distance = analogUltrasonic.GetValue() * ValueToInches;
    return distance;
}

void Ultrasonic::Enable() {
    ultrasonicState = ultrasonicOn;
   // ctrl->Set(ultrasonicOn);
}

void Ultrasonic::Disable() {
    ultrasonicState = ultrasonicOff;
  //  ctrl->Set(ultrasonicOff);
}