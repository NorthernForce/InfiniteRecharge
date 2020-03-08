/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/AutoPrintLine.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "commands/autonomous/AutoPrintLine.h"

AutoPrintLine::AutoPrintLine() {
  // Use addRequirements() here to declare subsystem dependencies.
    frc2::SequentialCommandGroup {
    AutoPrintLine(),
  }; 

}

