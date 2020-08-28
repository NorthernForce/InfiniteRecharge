/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <iostream>
using namespace std;

class Logger : public frc2::SubsystemBase {
 public:
  Logger();
  void Periodic();
  void LoadDataToFile(string varName, double varValue);
  void LoadDataToFile(string varName, string varValue);
  void LoadDataToFile(string varName, int varValue);
  void LoadDataToFile(string varName, bool varValue);
};
