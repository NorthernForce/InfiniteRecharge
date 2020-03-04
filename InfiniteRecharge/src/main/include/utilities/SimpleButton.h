/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/GenericHID.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/Command.h>


class SimpleButton {
 public:
  SimpleButton(frc::GenericHID* controller, int button);
  frc2::Button WhenPressed(frc2::Command*);
  frc2::Button WhenReleased(frc2::Command*);
  frc2::Button WhileHeld(frc2::Command*);

 private:
  frc::GenericHID* m_controller;
  int m_button;
};