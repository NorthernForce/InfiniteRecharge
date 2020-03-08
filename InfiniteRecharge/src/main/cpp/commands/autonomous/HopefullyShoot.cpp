/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/HopefullyShoot.h"
#include <frc2/command/SequentialCommandGroup.h>
#include "RobotContainer.h"
#include "commands/AutoDrive.h"
#include "commands/AimShooterUp.h"
#include "commands/MoveToLimelight.h"
#include "commands/ShootCell.h"


HopefullyShoot::HopefullyShoot() {
  distToGo = 169 - RobotContainer::ultrasonic->GetDistance();
  RobotContainer::shooter->SetRPM(3000);

  frc2::SequentialCommandGroup {
    MoveToLimelight(),
    AimShooterUp(),
    AutoDrive(distToGo, -0.2, -0.2),
    ShootCell()
  };
  RobotContainer::shooter->SetRPM(2200);
}

bool HopefullyShoot::IsFinished() { 
  return false; 
} 