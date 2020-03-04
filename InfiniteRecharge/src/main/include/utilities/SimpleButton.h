/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/Joystick.h>
#include <frc2/command/button/Button.h>


class SimpleButton {
 public:
  SimpleButton(frc::Joystick* controller, int button);
  frc2::Button Get();

 private:
  frc::Joystick* m_controller;
  int m_button;
};