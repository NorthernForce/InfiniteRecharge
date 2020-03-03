/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/FMSWheelComms.h"
#include <frc/DriverStation.h>
#include <string>

FMSWheelComms::FMSWheelComms() {
    if(gameData.length() > 0)
        GetGameData();
}

void FMSWheelComms::GetGameDataRequirements() {
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

char FMSWheelComms::GetGameData() {
    desiredColor = gameData[0];
    return desiredColor;
}