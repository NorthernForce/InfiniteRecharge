/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/Triangle.h"
#include "utilities/TriangleCalculator.h"

// creates an empty triangle
Triangle::Triangle() {}

Triangle::Triangle(double side_a, double side_b, double side_c, double ang_a, double ang_b, double ang_c)
 : a(side_a), b(side_b), c(side_c), A(ang_a), B(ang_b), C(ang_c) {}

double Triangle::GetAngleA() { return A; }

double Triangle::GetAngleB() { return B; }

double Triangle::GetAngleC() { return C; }

double Triangle::GetSideA() { return a; }

double Triangle::GetSideB() { return b; }

double Triangle::GetSideC() { return c; }

bool Triangle::HasErrors() {
    std::vector<double> allTriangleProps= {a, b, c, A, B, C};
    std::vector<double> angles = {A, B, C};

    for (auto prop : allTriangleProps) {
        if (prop == 0)
            return true;
        if (prop < 0)
            return true;
    }
    for (auto ang : angles)
        if (abs(ang) >= 180) {
            return true;
    }
    if (abs(angles[0]) + abs(angles[1]) + abs(angles[2]) > 180)
        return true;
        
    return false;
}