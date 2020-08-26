/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "utilities/Triangle.h"
#include <memory>
#include <vector>

class TriangleCalculator {
 public:
    TriangleCalculator(std::unique_ptr<Triangle> t);
    std::unique_ptr<Triangle> SAS();
    std::unique_ptr<Triangle> AAS();
    std::unique_ptr<Triangle> ASA();
    std::unique_ptr<Triangle> SSS();
    std::unique_ptr<Triangle> HL();

    double ThirdAngleCalc(double angle_a, double angle_b);
    double ThirdSideCalc(double side, double angle_a, double angle_c);
    double DegToRad(double deg);
    double RadToDeg(double rad);
    void ThrowExceptionOnErrors(std::vector<double> measurements);

    struct BaseException : public std::exception {};
    struct ZeroError : public BaseException {
        const char * what () const throw () {
            return "ZeroError: more than one required value is zero.\nTry entering 3 positive values.\n";
        }
    };
    struct AngleError : public BaseException {
        const char * what () const throw () {
            return "AngleError: one or more angles is too large.\nTry entering angles with a sum of 180.\n";
        }
    };
    struct NegativeError : public BaseException {
        const char * what () const throw () {
            return "NegativeError: one or more sides or angles is negative.\n";
        }
    };

 private:
    double side_a;
    double side_b;
    double side_c;
    double angle_a;
    double angle_b;
    double angle_c;
};
