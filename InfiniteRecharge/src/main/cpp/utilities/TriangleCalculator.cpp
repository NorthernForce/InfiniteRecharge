/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <cmath>
#include <iostream>
#include "utilities/TriangleCalculator.h"

TriangleCalculator::TriangleCalculator(std::unique_ptr<Triangle> t) {
    side_a = t->GetSideA();
    side_b = t->GetSideB();
    side_c = t->GetSideC();
    angle_a = t->GetAngleA();
    angle_b = t->GetAngleB();
    angle_c = t->GetAngleC();
}

Triangle TriangleCalculator::SAS() {
    Triangle triangle;

    if (side_b && side_c && angle_a != 0) {
        side_a = sqrt(pow(side_b,2) + pow(side_c,2) - 2*side_b*side_c * cos(DegToRad(angle_a)));
        triangle = SSS();
    }
    else if (side_a && side_c && angle_b != 0) {
        side_b = sqrt(pow(side_a,2) + pow(side_c,2) - 2*side_a*side_c * cos(DegToRad(angle_b)));
        triangle = SSS();
    }
    else if (side_a && side_b && angle_c != 0) {
        side_c = sqrt(pow(side_a,2) + pow(side_b,2) - 2*side_a*side_b * cos(DegToRad(angle_c)));
        triangle = SSS();
    }
    else {
        std::cerr << "ZeroError: One or more specified numbers is zero.\nPlease enter at least 3 positive numbers.\n";
    }

    return triangle;
}

Triangle TriangleCalculator::AAS() {

    angle_c = ThirdAngleCalc(angle_a, angle_c);
    side_a = ThirdSideCalc(side_c, angle_b, angle_c);
    side_b = ThirdSideCalc(side_c, angle_b, angle_c);

    return Triangle(side_a, side_b, side_c, angle_a, angle_b, angle_c);
}

Triangle TriangleCalculator::ASA() {
    angle_c = ThirdAngleCalc(angle_a, angle_b);
    side_a = ThirdSideCalc(side_c, angle_a, angle_c);
    side_b = ThirdSideCalc(side_c, angle_b, angle_c);

    return Triangle(side_a, side_b, side_c, angle_a, angle_b, angle_c);
}

Triangle TriangleCalculator::SSS() {
    angle_a = RadToDeg(acos((pow(side_b,2) + pow(side_c,2) - pow(side_a,2)) / (2 * side_b * side_c)));
    angle_b = RadToDeg(acos((pow(side_c,2) + pow(side_a,2) - pow(side_b,2)) / (2 * side_c * side_a)));
    angle_c = ThirdAngleCalc(angle_a, angle_b);

    return Triangle(side_a, side_b, side_c, angle_a, angle_b, angle_c);
}

Triangle TriangleCalculator::HL() {
    angle_c = 90;

    side_a = sqrt(pow(side_c,2) - pow(side_b,2));
    angle_a = RadToDeg(acos((pow(side_b,2) + pow(side_a,2) - pow(side_a,2)) / (2 * side_b * side_a)));
    angle_b = RadToDeg(acos((pow(side_c,2) + pow(side_a,2) - pow(side_b,2)) / (2 * side_c * side_a)));

    return Triangle(side_a, side_b, side_c, angle_a, angle_b, angle_c);
}

double TriangleCalculator::ThirdAngleCalc(double ang_a, double ang_b) {
    double ang_c = (180-(ang_a+ang_b));
    return ang_c;
}

// Uses the Law of Sines
double TriangleCalculator::ThirdSideCalc(double side, double ang_a, double ang_c) {
    double newSide = abs(side*(sin(DegToRad(ang_a))) / sin(DegToRad(ang_c)));
    return newSide;
}

double TriangleCalculator::DegToRad(double deg) {
    return deg * (M_PI / 180);
}

double TriangleCalculator::RadToDeg(double rad) {
    return rad * (180 / M_PI);
}