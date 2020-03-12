/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Ultrasonic.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

//all digital stuff is commented out
Ultrasonic::Ultrasonic() {
    analogUltrasonic.reset(new frc::AnalogInput(Constants::ultrasonicRangeFinder));
    //ctrl.reset(new frc::DigitalOutput(Constants::Ultrasonic::digitalCtrlPort));
}

void Ultrasonic::Periodic() {
    isObstacleDetected = IsObstacleAt(12);
    distance = GetDistance();
    //std::cout << distance << "\n";
    frc::SmartDashboard::PutNumber("Ultrasonic distance: ", distance);
}


bool Ultrasonic::IsObstacleAt(int targetDistance) {
    if(distance < targetDistance) {
        return true;
    } else {
        return false;
    }
}

double Ultrasonic::GetDistance() {
    distance = analogUltrasonic->GetValue() * ValueToInches;
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

