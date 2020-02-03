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

        namespace GearRatio {
            const int low = 4.286;
            const int high = 1.176;
        };
        const int motorCPR = 42;
        const double wheelCPR_low = motorCPR * GearRatio::low;
        const double wheelCPR_high = motorCPR * GearRatio::high;
    }

    namespace OI {
        const int driverController_id = 0;
        const int manipulatorController_id = 1;
    }

    namespace PCM {
        const int PCMCanBusID = 11;
        const std::pair<int, int> shifterDS_id(2,3);
    }
}
