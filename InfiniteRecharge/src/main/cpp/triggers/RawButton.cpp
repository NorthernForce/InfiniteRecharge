/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/RawButton.h"
#include "OI.h"

template<class T> RawButton<T>::RawButton(std::shared_ptr<frc::GenericHID> joystick, T buttonNumber) :
 m_joystick(joystick), m_buttonNumber(buttonNumber) {}

template<class T> bool RawButton<T>::Get() {
    return m_joystick->GetRawButton(static_cast<int>(m_buttonNumber));
}

template class RawButton<OI::Xbox>;