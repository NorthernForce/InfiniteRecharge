/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"

Limelight::Limelight() {
    table->PutNumber("ledMode", 1);
}

// This method will be called once per scheduler run
void Limelight::Periodic() {}

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

std::shared_ptr<NetworkTable> Limelight::GetTable() {
    return table;
}