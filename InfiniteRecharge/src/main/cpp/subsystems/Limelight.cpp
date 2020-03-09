/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include <frc/smartdashboard/SmartDashboard.h>

Limelight::Limelight() {
    table->PutNumber("camMode", 0);
    table->PutNumber("ledMode", 1);
}

// This method will be called once per scheduler run
void Limelight::Periodic() {
    frc::SmartDashboard::PutNumber("Limelight OffsetX: ", GetXOffset());
}

double Limelight::GetXOffset() {
    double targetOffsetAngleX = table->GetNumber("tx",0);
    return targetOffsetAngleX;
}

bool Limelight::IsTargetThere() {
    bool IsTargetThere = table->GetNumber("tv", 0);
    return IsTargetThere;
}

double Limelight::GetTargetArea() {
    double targetArea = table->GetNumber("ta",0);
    return targetArea;
}

double Limelight::GetTargetSkew() {
    double targetSkew = table->GetNumber("ts",0);
    return targetSkew;
}

void Limelight::PutNumberToTable(std::string key, double number) {
    table->PutNumber(key, number);
}

double Limelight::GetNumberFromTable(std::string key, double defaultValue) {
    double value = table->GetNumber(key, defaultValue);
    return value;
}