/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/XboxController.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/Command.h>


class SimpleButton {
 public:
  SimpleButton(std::shared_ptr<frc::XboxController> controller, int button);
  bool Get();

 private:
  std::shared_ptr<frc::XboxController> m_controller;
  int m_button;
};