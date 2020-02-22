/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/utilities/FMSWheelInterface.h"
#include <frc/DriverStation.h>

FMSWheelInterface::FMSWheelInterface() {
    if(gameData.length() > 0) {
        GetGameData();
    }
}

void FMSWheelInterface::GameDataRequirements() {
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

void FMSWheelInterface::GetGameData() {
    {
    switch (gameData[0])
    {
        case 'B' :
        desiredColor = 'Blue';
        break;
        case 'G' :
        desiredColor = 'Green';
        break;
        case 'R' :
        desiredColor = 'Red';
         break;
        case 'Y' :
         desiredColor = 'Yellow';
          break;
        default :
         desiredColor = 'None';
         break;
        
}
    }
    }