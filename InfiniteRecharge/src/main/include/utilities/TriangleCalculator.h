/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "utilities/Triangle.h"
#include <memory>

class TriangleCalculator {
 public:
    TriangleCalculator(std::unique_ptr<Triangle> t);
    Triangle SAS();
    Triangle AAS();
    Triangle ASA();
    Triangle SSS();
    Triangle HL();

    double ThirdAngleCalc(double angle_a, double angle_b);
    double ThirdSideCalc(double side, double angle_a, double angle_c);
    double DegToRad(double deg);
    double RadToDeg(double rad);

 private:
    double side_a;
    double side_b;
    double side_c;
    double angle_a;
    double angle_b;
    double angle_c;
};
