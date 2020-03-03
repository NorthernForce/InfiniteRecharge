/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "subsystems/WackyWheel.h"
#include "Constants.h"
#include "rev/ColorSensorV3.h"
#include "utilities/FMSWheelComms.h"

WackyWheel::WackyWheel() {
    colorSensor.reset(new rev::ColorSensorV3(frc::I2C::Port::kOnboard));
    spinnerTalon.reset(new WPI_TalonSRX(Constants::MotorIDs::wackyWheel));
    getDesiredColor.reset(new FMSWheelComms);
    AddColorMatches();
}

void WackyWheel::Periodic() {
    detectedColor = colorSensor->GetColor();
    matchedColor = colorMatcher->MatchClosestColor(detectedColor, confidence);
    desiredColor = getDesiredColor->GetGameData();
    FindColor();
} 

void WackyWheel::AddColorMatches() {
    colorMatcher->AddColorMatch(blueTarget);
    colorMatcher->AddColorMatch(greenTarget);
    colorMatcher->AddColorMatch(redTarget);
    colorMatcher->AddColorMatch(yellowTarget);
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

void WackyWheel::GoToFMSColor() {
  if (colorChar != desiredColor) {
    if((colorChar ==  'Y') && (desiredColor == 'R'))
      spinnerTalon->Set(-0.2);
    else if ((colorChar == 'B') && (desiredColor = 'Y'))
      spinnerTalon->Set(-0.2);
    else if ((colorChar == 'G') && (desiredColor == 'B'))
      spinnerTalon->Set(-0.2);
    else if ((colorChar == 'R') && (desiredColor == 'G'))
      spinnerTalon->Set(-0.2);
    else
      spinnerTalon->Set(0.2);
  }
  else if (colorChar == desiredColor)
    spinnerTalon->SetNeutralMode(NeutralMode::Brake);
}

void WackyWheel::Rotate(int rotations) {
  if (WackyWheel::colorPasses < 2*rotations) {
    spinnerTalon->Set(0.2);
    if ((WackyWheel::colorChar == firstColor) && (counterFrozen == false)) {
      WackyWheel::colorPasses ++;
      counterFrozen = true;
    }
    else if (WackyWheel::colorChar != firstColor)
      counterFrozen = false;
  }
}