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
 : m_a(side_a), m_b(side_b), m_c(side_c), m_A(ang_a), m_B(ang_b), m_C(ang_c) {}

double Triangle::GetAngleA() { return m_A; }

double Triangle::GetAngleB() { return m_B; }

double Triangle::GetAngleC() { return m_C; }

double Triangle::GetSideA() { return m_a; }

double Triangle::GetSideB() { return m_b; }

double Triangle::GetSideC() { return m_c; }