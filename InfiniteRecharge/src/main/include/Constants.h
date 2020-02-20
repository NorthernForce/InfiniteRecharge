/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace Constants {
    namespace Drivetrain {
        const int leftPrimary = 4;
        const int leftFollower1 = 6;
        const int leftFollower2 = 2;

        const int rightPrimary = 5;
        const int rightFollower1 = 1;
        const int rightFollower2 = 3;

        const double initialStage = 12/42;     //  Driven gear / Shifting Grear
        const double shiftingHigh = 44/31;     //  Driver Gear / High Shifting Gear
        const double shiftingLow =  60/14;     //  Driver Gear / Low Shifting Gear

        namespace Gear {
            const double low = initialStage*shiftingLow
            const double high = initialStage*shiftingHigh;
        }
    }
    namespace Shooter {
        const int primary = 0;
        const int follower1 = 0;
        const int follower2 = 0;
        const int follower3 = 0;
    }
    namespace Encoders {
        const double pi = 3.141592653589793;
        const int motorCPR = 42;
        const double wheelCPR_low = motorCPR * Constants::Drivetrain::Gear::low;
        const double wheelCPR_high = motorCPR * Constants::Drivetrain::Gear::high;
        const double wheelCircum = 6 * pi;
        const int rotationMultiplier = 5;
    }

    namespace OI {
        const int driverController_id = 0;
        const int manipulatorController_id = 1;
    }

    namespace PCM {
        const int PCMCanBusID = 11;
    }

    namespace Servo {
        const int panServo = 0;
        const int tiltServo = 1;
    }

    namespace Ultrasonic {
        const int ultrasonicRangeFinder = 0; // analog port 0
      //  const int digitalCtrlPort = 9; 
    }

    namespace Intake {
        const int intakeMotor = 10; ////TODO: have to reassign these when we actually have the robot
        const int armMotor = 11;
        
        const bool armIsDown = true;
        const bool armIsUp = false;
    }
    
}
