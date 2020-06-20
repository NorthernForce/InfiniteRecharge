/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

class Triangle {
 public:
    Triangle();
    Triangle(double a, double b, double c, double A, double B, double C);

    double GetAngleA();
    double GetAngleB();
    double GetAngleC();
    double GetSideA();
    double GetSideB();
    double GetSideC();

 private:
    double A;
    double B;
    double C;
    double a;
    double b;
    double c;
};
