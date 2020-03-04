/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/SimpleButton.h"

SimpleButton::SimpleButton(frc::Joystick* controller, int button) 
 : m_controller(controller), m_button(button) {}

frc2::Button SimpleButton::Get() {
    return frc2::Button([this] { return m_controller->GetRawButton(m_button); });
}