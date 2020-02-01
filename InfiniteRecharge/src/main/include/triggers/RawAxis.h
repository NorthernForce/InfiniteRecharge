/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/button/Trigger.h>
#include <frc/GenericHID.h>

template<class T> class RawAxis : public frc2::Trigger {
 public:
    RawAxis(std::shared_ptr<frc::GenericHID> joystick, T axis, double lowerLimit=0.5, double upperLimit=1.0);
    bool Get();
 private:
    std::shared_ptr<frc::GenericHID> m_joystick;
    T m_axis;
    double m_lowerLimit;
    double m_upperLimit;
};
