/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/FMSWheelInterface.h"
#include <frc/DriverStation.h>
#include <string>

FMSWheelInterface::FMSWheelInterface() {
    if(gameData.length() > 0) {
        GetGameData();
    }
}

void FMSWheelInterface::GameDataRequirements() {
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

char FMSWheelInterface::GetGameData() {
    desiredColor = gameData[0];
    return desiredColor;
}