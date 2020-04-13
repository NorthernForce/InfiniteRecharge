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

    const double ultrasonicDistFromRoboCent = 14;

    const double pi = 3.141592653589793;
    const double degreesToRadians = pi/180;

    const int XResetMultiplier = 0.996194698092;

    const int lowDriveMultiplier = -.7179821429;
    const int highDriveMultiplier = -.269272619;
    
    namespace MotorIDs {
        const int driveLeftPrimary = 5;
        const int driveLeftFollower1 = 1;
        const int driveLeftFollower2 = 3;
        const int driveRightPrimary = 6;
        const int driveRightFollower1 = 2;
        const int driveRightFollower2 = 4;

        const int shooter = 8;
        const int wackyWheel = 11; 

        const int intake = 13;  

        const int intakeArm = 9;
        const int conveyor1 = 10;
        const int conveyor2 = 12;

        const int climberArm = 7;

        const int panServoPWM = 7;
        const int tiltServoPWM = 8;

    }

    namespace Intake {
        const int slow = -0.25;
        const int normal = -0.45;
        const int fast = -0.7;
    }

    namespace Shifting {
        const double lowMultiplier = 4.286;
        const double highMultiplier = 1.39383333333333333333;
    }

    namespace DigitalPort { 
        const int ballPort0 = 0; 
        const int ballPort1 = 1;
        const int ballPort2 = 2;
        const int ballPort3 = 3;
        const int ballPort4 = 4;
        const int ballPort5 = 5;

        const int redRGB = 10;
        const int greenRGB = 11;
        const int blueRGB = 12;
    }
}