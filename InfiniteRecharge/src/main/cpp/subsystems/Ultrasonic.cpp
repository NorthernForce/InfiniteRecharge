/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Ultrasonic.h"


Ultrasonic::Ultrasonic() {}

// This method will be called once per scheduler run
void Ultrasonic::Periodic() {
    if (ultrasonicOn) {
        distance = analogUltrasonic.GetValue() * ValueToInches;
    }

    else {
        distance = 0;
    }
}

double Ultrasonic::GetDistance() {
    return distance;
}

void Ultrasonic::Enable() {
    ultrasonicState = ultrasonicOn;
}

void Ultrasonic::Disable() {
    ultrasonicState = ultrasonicOff;
}