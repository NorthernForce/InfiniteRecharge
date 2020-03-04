/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/SimpleButton.h"

SimpleButton::SimpleButton(frc::GenericHID* controller, int button) 
 : m_controller(controller), m_button(button) {}

frc2::Button SimpleButton::WhenPressed(frc2::Command* command) {
    return frc2::Button([this] { return m_controller->GetRawButton(m_button); }).WhenPressed(command);
}

frc2::Button SimpleButton::WhenReleased(frc2::Command* command) {
    return frc2::Button([this] { return m_controller->GetRawButton(m_button); }).WhenReleased(command);
}

frc2::Button SimpleButton::WhileHeld(frc2::Command* command) {
    return frc2::Button([this] { return m_controller->GetRawButton(m_button); }).WhileHeld(command);
}