/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/ComboControl.h"

ComboControl::ComboControl(frc2::Trigger* control1, frc2::Trigger* control2) :
 m_control1(control1), m_control2(control2) {}

bool ComboControl::Get() {
    return (m_control1 && m_control2);
}