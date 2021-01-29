/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/InFrontOfOurTrench.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <iostream>

#include "commands/TurnToAngle.h"
#include "commands/IntakeDown.h"
#include "commands/AutoDrive.h"
#include "commands/IntakeUp.h"

InFrontOfOurTrench::InFrontOfOurTrench() {
  std::cout << "Your auto is a failure" << std::endl,
  frc2::SequentialCommandGroup {
    TurnToAngle(180),
    IntakeDown(),
    AutoDrive(144),
    IntakeUp()
  };
}