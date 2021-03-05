/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/AICommunication.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "RobotContainer.h"
#include <iostream>

AICommunication::AICommunication() {}

// This method will be called once per scheduler run
void AICommunication::Periodic() {
    std::cout << "Offset in cam: " << GetCamTargetOffsets(AIVisionTargetting::Target::Powercell)[0] << '\n';
}

bool AICommunication::IsTargetFound() {
    bool isTargetFound = static_cast<bool>(frc::SmartDashboard::GetNumber("valid target:", 0));
    return isTargetFound;
}

Target AICommunication::GetTargetType() {
    auto type = Target::None;
    auto targetType = frc::SmartDashboard::GetString("targetType:", "pc");

    if (targetType == "pc")
        type = Target::Powercell;
    else if (targetType == "goal")
        type = Target::Goal;
    return type;
}

std::vector<double> AICommunication::GetCamTargetOffsets(Target targetType) {
    std::vector<double> targetOffset;
    if (targetType == Target::Powercell)
        targetOffset = GetValueArray(pcOffsetInCam_label);
    // add goal targetting later
    return targetOffset;    
}

double AICommunication::GetPCOffsetInCameraX() {
    return RobotContainer::aiComms->GetCamTargetOffsets(powercell)[0];
}

double AICommunication::GetDistanceToTarget() {
    return frc::SmartDashboard::GetNumber("Distance To Target:", 0);
}

std::vector<double> AICommunication::GetValueArray(std::string key) {
    auto data = frc::SmartDashboard::GetNumberArray(key, -1);
    return data;
}

double AICommunication::GetNumber(std::string key) {
    return frc::SmartDashboard::GetNumber(key, -1);
}

void AICommunication::SwitchCameraToIntake() {
    frc::SmartDashboard::PutNumber("AI Cam", 1);
}

void AICommunication::SwitchCameraToGimbal() {
    frc::SmartDashboard::PutNumber("AI Cam", 0);
}