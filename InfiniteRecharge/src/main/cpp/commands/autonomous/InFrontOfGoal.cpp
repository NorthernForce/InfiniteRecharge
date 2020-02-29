/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/InFrontOfGoal.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "commands/TurnToAngle.h"
#include "commands/AutoDrive.h"
#include "commands/IntakeDown.h"
#include "commands/IntakeUp.h"
#include "commands/IntakePowerCell.h"

InFrontOfGoal::InFrontOfGoal() {
  frc2::SequentialCommandGroup {
    TurnToAngle(90),
    AutoDrive(48),
    TurnToAngle(90),
    IntakeDown(),
  };

    frc2::ParallelCommandGroup {
      IntakePowerCell(),
      AutoDrive(219),
    };

  frc2::SequentialCommandGroup {
    AutoDrive(-168),
  };
}