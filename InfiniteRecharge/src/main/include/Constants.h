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

    const int PCMCanBusID = 11;
    const int ultrasonicRangeFinder = 0;
    
    namespace MotorIDs {
        const int driveLeftPrimary = 4;
        const int driveLeftFollower1 = 6;
        const int driveLeftFollower2 = 2;
        const int driveRightPrimary = 5;
        const int driveRightFollower1 = 1;
        const int driveRightFollower2 = 3;

        const int shooterPrimary = 0;
        const int shooterFollower1 = 0;
        const int shooterFollower2 = 0;
        const int shooterFollower3 = 0;

        const int wackyWheel = 0;

        const int intake = 10;
        const int intakeArm = 11;
        const int conveyor1 = 0;
        const int conveyor2 = 0;

        const int climberArm = 13;

        const int panServoPWM = 0;
        const int tiltServoPWM = 1;
    }

    namespace Shifting {
        const double initialStage = 12/42;
        const double shiftingHigh = 44/31;
        const double shiftingLow =  60/14;

        const double pi = 3.141592653589793;
        const double wheelCircum = 6 * pi;
        const int rotationMultiplier = 5;

        namespace Gear {
            const double low = initialStage*shiftingLow;
            const double high = initialStage*shiftingHigh;
        }
    }

    namespace DigitalPort { 
        const int ballPort0 = 0; 
        const int ballPort1 = 1;
        const int ballPort2 = 2;
        const int ballPort3 = 3;
        const int ballPort4 = 4;
        const int ballPort5 = 5;
    }
}