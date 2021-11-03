/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace Constants {
    const int driverController_id = 0;
    const int manipulatorController_id = 1;

    const int PCMCanBusID = 15;
    const int ultrasonicRangeFinder = 1;

    const double roboWidth = 29;
    const double roboLength = 30.5;
    const double bumperThickness = 3;

    const double camDistFromRoboFrontCent = 9;
    const double camDistFromRoboSideCent = 9;
    const double camDistFromRoboCenter = 13.5;
    const double intakeDistFromRoboCenter = 22;

    const double ultrasonicDistFromRoboCent = 14;

    const double pi = 3.141592653589793;
    const double degreesToRadians = pi/180;

    const double XResetMultiplier = 0.996194698092;
    
    namespace MotorIDs {
        const int driveLeftPrimary = 5;
        const int driveLeftFollower1 = 1;
        const int driveLeftFollower2 = 3;
        const int driveRightPrimary = 6;
        const int driveRightFollower1 = 2;
        const int driveRightFollower2 = 4;

        const int susan = 11;
        const int hood = 7;

        const int shooter = 8;
        
        const int intake = 13;  

        const int intakeArm = 9;
        const int conveyor1 = 10;
        const int conveyor2 = 12;

        const int panServoPWM = 7;
        const int tiltServoPWM = 8;

    }

    namespace Intake {
        const double slow = -0.325;
        const double normal = -0.45;
        const double fast = -0.7;
    }

    namespace Shifting {
        const double lowMultiplier = .7179821429;
        const double highMultiplier = 0.2892773749374815;
    }

    namespace DigitalPort { 
        const uint8_t ballPort0 = 0; 
        const uint8_t ballPort1 = 1;
        const uint8_t ballPort2 = 2;
        const uint8_t ballPort3 = 3;
        const uint8_t ballPort4 = 4;
        const uint8_t ballPort5 = 5;

        const uint8_t susanLimitSwitch = 9;

        const uint8_t redRGB = 10;
        const uint8_t greenRGB = 11;
        const uint8_t blueRGB = 12;
    }
}