// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <vector>
#include <string>

class InteractTextFiles {
 public:
  InteractTextFiles();
  void WriteTextFile(std::vector<double>, std::string);
  std::vector<double> ReadTextFile(std::string fileName);
};
