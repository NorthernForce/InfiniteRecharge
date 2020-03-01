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
void Limelight::Periodic() {
    GetXOffset();
    GetTargetAreaSkew();
    IsTargetThere();
}

double Limelight::GetXOffset() {
    double targetOffsetAngleX = table->GetNumber("tx",0.0);
    return targetOffsetAngleX;
}

bool Limelight::IsTargetThere() {
    double IsTargetThere = table->GetNumber("tv", 0.0);
    return IsTargetThere;
}

std::pair<double, double> Limelight::GetTargetAreaSkew() {
    double targetArea = table->GetNumber("ta",0.0);
    double targetSkew = table->GetNumber("ts",0.0);
    return std::make_pair(targetArea, targetSkew);
}

std::shared_ptr<NetworkTable> Limelight::GetTable() {
    return table;
}