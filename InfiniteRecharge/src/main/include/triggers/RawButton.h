/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/button/Trigger.h>
#include <frc/GenericHID.h>

template<class T> class RawButton : public frc2::Trigger {
 public:
    RawButton(std::shared_ptr<frc::GenericHID> joystick, T buttonNumber);
    bool Get();
 private:
    std::shared_ptr<frc::GenericHID> m_joystick;
    T m_buttonNumber;
};
