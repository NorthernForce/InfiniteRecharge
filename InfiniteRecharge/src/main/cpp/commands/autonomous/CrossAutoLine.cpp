/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/CrossAutoLine.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "commands/AutoDrive.h"
#include <iostream>

CrossAutoLine::CrossAutoLine() {
  frc2::SequentialCommandGroup {
    AutoDrive(36)
  };
}