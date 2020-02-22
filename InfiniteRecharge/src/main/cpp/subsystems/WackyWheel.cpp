/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "subsystems/WackyWheel.h"
#include "Constants.h"
#include "rev/ColorSensorV3.h"
#include "subsystems/utilities/FMSWheelInterface.h"


WackyWheel::WackyWheel() {
    colorSensor.reset(new rev::ColorSensorV3(frc::I2C::Port::kOnboard));
    spinner.reset(new WPI_TalonSRX(Constants::MotorIDs::wackyWheel));
    getDesiredColor.reset(new FMSWheelInterface);
    AddColorMatches();
}

void WackyWheel::Periodic() {
    detectedColor = colorSensor->GetColor();
    matchedColor = colorMatcher->MatchClosestColor(detectedColor, confidence);
    desiredColor = getDesiredColor->GetGameData();
    FindColor();
} 

void WackyWheel::AddColorMatches(){
    colorMatcher->AddColorMatch(blueTarget);
    colorMatcher->AddColorMatch(greenTarget);
    colorMatcher->AddColorMatch(redTarget);
    colorMatcher->AddColorMatch(yellowTarget);
}

void WackyWheel::MoveToColor() {
  if (colorChar == desiredColor) {
    spinner->Set(0.2);
  } else if (colorChar != desiredColor) {
    spinner->SetNeutralMode(NeutralMode::Brake);
  }
}
void WackyWheel::FindColor() {
    
    if (detectedColor == blueTarget) 
      colorChar = 'B';
    else if (detectedColor == redTarget)
      colorChar = 'R';
    else if (detectedColor == greenTarget)
      colorChar = 'G';
    else if (detectedColor == yellowTarget)
      colorChar = 'Y';
    else
      colorChar = 'N';
}

