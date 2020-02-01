/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/button/Trigger.h>

class ComboControl : public frc2::Trigger {
 public:
    ComboControl(frc2::Trigger* control1, frc2::Trigger* control2);
    bool Get();
 private:
    frc2::Trigger *m_control1;
    frc2::Trigger *m_control2;
};
