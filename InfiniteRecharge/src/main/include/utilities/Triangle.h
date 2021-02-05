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
    Triangle(double side_a, double side_b, double side_c, double ang_a, double ang_b, double ang_c);

    double GetAngleA();
    double GetAngleB();
    double GetAngleC();
    double GetSideA();
    double GetSideB();
    double GetSideC();
    bool HasErrors();

 private:
    double a;
    double b;
    double c;
    double A;
    double B;
    double C;
};
