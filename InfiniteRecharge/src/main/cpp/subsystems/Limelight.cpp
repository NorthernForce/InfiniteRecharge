/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"

Limelight::Limelight() {}

// This method will be called once per scheduler run
void Limelight::Periodic() {
    XOffset();
    TargetAreaSkew();
    IsTargetThere();
}

double Limelight::XOffset() {
    double targetOffsetAngleX = table->GetNumber("tx",0.0);
    return targetOffsetAngleX;
}

bool Limelight::IsTargetThere() {
    double IsTargetThere = table->GetNumber("tv", 0.0);
    return IsTargetThere;
}

std::pair<double, double> Limelight::TargetAreaSkew() {
    double targetArea = table->GetNumber("ta",0.0);
    double targetSkew = table->GetNumber("ts",0.0);
    return std::make_pair(targetArea, targetSkew);
}
