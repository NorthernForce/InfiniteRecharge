/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/Triangle.h"

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