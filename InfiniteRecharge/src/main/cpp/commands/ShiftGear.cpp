/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShiftGear.h"
#include <frc/DriverStation.h>

ShiftGear::ShiftGear(Gear gear) :
  m_gear(gear) {
    AddRequirements(RobotContainer::drivetrain.get());
    AddRequirements(RobotContainer::driveShifter.get());
    strcpy(logMessage, m_gear == Gear::Low ? "Shift to low" : "Shift to high");
}

void ShiftGear::Initialize() {
  frc::DriverStation::ReportWarning(logMessage);
  RobotContainer::driveShifter->Shift(m_gear);
}

bool ShiftGear::IsFinished() {
  return RobotContainer::driveShifter->IsShiftDone();
}
