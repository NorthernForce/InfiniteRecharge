/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/Triangle.h"

// creates an empty triangle
Triangle::Triangle() {}

// triangles use normal naming scheme:
// sides- abc (c can be bottom)
// angles- ABC (<C can be top)
// Use zeros for unknown arguments, only three required
Triangle::Triangle(double a, double b, double c, double A, double B, double C)
 : a(a), b(b), c(c), A(A), B(B), C(C) {}

double Triangle::GetAngleA() { return A; }

double Triangle::GetAngleB() { return B; }

double Triangle::GetAngleC() { return C; }

double Triangle::GetSideA() { return a; }

double Triangle::GetSideB() { return b; }

double Triangle::GetSideC() { return c; }