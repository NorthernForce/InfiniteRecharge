/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/SimpleAxis.h"

SimpleAxis::SimpleAxis(std::shared_ptr<frc::GenericHID> joystick, int axis, double threshold)
 : m_joystick(joystick), m_axis(axis), m_threshold(threshold) {}

bool SimpleAxis::Get() {
    double value = m_joystick->GetRawAxis(m_axis);
    bool isAxisPressed = false;
    if (value > m_threshold)
        isAxisPressed = true;
    return isAxisPressed;
}