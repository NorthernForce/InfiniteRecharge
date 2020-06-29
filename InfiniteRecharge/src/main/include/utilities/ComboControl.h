/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/GenericHID.h>

class ComboControl {
 public:
  ComboControl(std::shared_ptr<frc::GenericHID> joystick, int button1, int button2);
  bool Get();
 private:
  std::shared_ptr<frc::GenericHID> currentJoystick;
  int button1;
  int button2;
};
