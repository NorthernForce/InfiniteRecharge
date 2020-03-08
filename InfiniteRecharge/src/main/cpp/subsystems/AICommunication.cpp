/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/AICommunication.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

AICommunication::AICommunication() {}

std::vector<double> AICommunication::GetValueArray(std::string key) {
    auto data = frc::SmartDashboard::GetNumberArray(key, 0);
    return data;
}

double AICommunication::GetNumber(std::string key) {
    return frc::SmartDashboard::GetNumber(key, 0);
}

// This method will be called once per scheduler run
void AICommunication::Periodic() {
    auto aiCamOff = GetValueArray(powercellOffsetInCam);
    //std::cout << aiCamOff[0] << ", " << aiCamOff[1] << '\n';
}