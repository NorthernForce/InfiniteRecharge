/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

#include "subsystems/WackyWheel.h"
#include "Constants.h"
#include "rev/ColorSensorV3.h"

WackyWheel::WackyWheel() {
    colorSensor.reset(new rev::ColorSensorV3(frc::I2C::Port::kOnboard));
    primary.reset(new rev::CANSparkMax(Constants::ColorSensor::primary, rev::CANSparkMax::MotorType::kBrushless));
    colorMatcher->AddColorMatch(blueTarget);
    colorMatcher->AddColorMatch(greenTarget);
    colorMatcher->AddColorMatch(redTarget);
    colorMatcher->AddColorMatch(yellowTarget);
}

void WackyWheel::Periodic() {
    detectedColor = colorSensor->GetColor();
    matchedColor = colorMatcher->MatchClosestColor(detectedColor, confidence);
    FindColor();
} 

void WackyWheel::FindColor() {
    
    if (detectedColor == blueTarget) 
      colorString = "Blue";
    else if (detectedColor == redTarget)
      colorString = "Red";
    else if (detectedColor == greenTarget)
      colorString = "Green";
    else if (detectedColor == yellowTarget)
      colorString = "Yellow";
    else
      colorString = "Unknown";
}

