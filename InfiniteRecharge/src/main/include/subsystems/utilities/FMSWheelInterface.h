/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

class FMSWheelInterface {
 public:
  FMSWheelInterface();
  void GetGameData();
  void GameDataRequirements();
 private:
  std::string gameData;
  std::string desiredColor;
};
