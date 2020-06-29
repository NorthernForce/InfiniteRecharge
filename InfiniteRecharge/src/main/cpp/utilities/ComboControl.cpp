/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/ComboControl.h"

ComboControl::ComboControl(std::shared_ptr<frc::GenericHID> joystick, int button1, int button2) 
 : currentJoystick(joystick), button1(button1), button2(button2) {}

bool ComboControl::Get() {
    bool b1 = currentJoystick->GetRawButton(button1);
    bool b2 = currentJoystick->GetRawButton(button2);
    if (b1 && b2)
        return true;
    else
        return false;
}