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
    const double robotRadius = sqrt(pow((roboWidth / 2),2) + pow(((roboLength + 12) / 2), 2));

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
        const double slow = -0.325;
        const double normal = -0.45;
        const double fast = -0.7;
    }

    namespace Shifting {
        const double lowMultiplier = .7179821429;
        const double highMultiplier = 0.2892773749374815;
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

    namespace CoordinatePlane {
        class Point {
         public:
            double x,y;
            Point(double x, double y)
            : x(x), y(y) {}
        };

        const Point A1 = Point(30,150);
        const Point A2 = Point(60,150);
        const Point A3 = Point(90,150);
        const Point A4 = Point(120,150);
        const Point A5 = Point(150,150);
        const Point A6 = Point(180,150);
        const Point A7 = Point(210,150);
        const Point A8 = Point(240,150);
        const Point A9 = Point(270,150);
        const Point A10 = Point(300,150);
        const Point A11 = Point(330,150);

        const Point B1 = Point(30,120);
        const Point B2 = Point(60,120);
        const Point B3 = Point(90,120);
        const Point B4 = Point(120,120);
        const Point B5 = Point(150,120);
        const Point B6 = Point(180,120);
        const Point B7 = Point(210,120);
        const Point B8 = Point(240,120);
        const Point B9 = Point(270,120);
        const Point B10 = Point(300,120);
        const Point B11 = Point(330,120);

        const Point C1 = Point(30,90);
        const Point C2 = Point(60,90);
        const Point C3 = Point(90,90);
        const Point C4 = Point(120,90);
        const Point C5 = Point(150,90);
        const Point C6 = Point(180,90);
        const Point C7 = Point(210,90);
        const Point C8 = Point(240,90);
        const Point C9 = Point(270,90);
        const Point C10 = Point(300,90);
        const Point C11 = Point(330,90);

        const Point D1 = Point(30,60);
        const Point D2 = Point(60,60);
        const Point D3 = Point(90,60);
        const Point D4 = Point(120,60);
        const Point D5 = Point(150,60);
        const Point D6 = Point(180,60);
        const Point D7 = Point(210,60);
        const Point D8 = Point(240,60);
        const Point D9 = Point(270,60);
        const Point D10 = Point(300,60);
        const Point D11 = Point(330,60);

        const Point E1 = Point(30,30);
        const Point E2 = Point(60,30);
        const Point E3 = Point(90,30);
        const Point E4 = Point(120,30);
        const Point E5 = Point(150,30);
        const Point E6 = Point(180,30);
        const Point E7 = Point(210,30);
        const Point E8 = Point(240,30);
        const Point E9 = Point(270,30);
        const Point E10 = Point(300,30);
        const Point E11 = Point(330,30);
    }
}