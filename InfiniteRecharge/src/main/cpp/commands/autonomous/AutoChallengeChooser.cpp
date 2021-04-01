// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoChallengeChooser.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/autonomous/MoveToCoordinate.h"
#include "commands/IntakePowerCell.h"


AutoChallengeChooser::AutoChallengeChooser() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AutoChallengeChooser::Initialize() {
  autoChooser = frc::SmartDashboard::GetNumber("Auto Path Input", 0);

  switch (autoChooser)
  {
  case 0:
    break;
  
  case 1:
  autoCommandScheduler.reset(new AutoCommandScheduler({     
        //Path A-Galactic
        //Red
        new IntakePowerCell(),
        new MoveToCoordinate(60, 30),
        new IntakePowerCell(),
        new MoveToCoordinate(120, 60),
        new IntakePowerCell(),
        new MoveToCoordinate(150, -30),
        new MoveToCoordinate(340, 0),
    }));
    break;
  case 2:
  autoCommandScheduler.reset(new AutoCommandScheduler({
        //Path A-Galactic
        //Blue
        new IntakePowerCell(),
        new MoveToCoordinate(150, 60),
        new IntakePowerCell(),
        new MoveToCoordinate(180, -60),
        new IntakePowerCell(),
        new MoveToCoordinate(240, -30),
        new MoveToCoordinate(340, 0),
    }));
    break;
  case 3:
  autoCommandScheduler.reset(new AutoCommandScheduler({
        //Path B-Galactic
        //Red
        new IntakePowerCell(),
        new MoveToCoordinate(60, 0),
        new IntakePowerCell(),
        new MoveToCoordinate(120, 60),
        new IntakePowerCell(),
        new MoveToCoordinate(180, 0),
        new MoveToCoordinate(340, 0),
    }));
    break;
  case 4:
  autoCommandScheduler.reset(new AutoCommandScheduler({
        //Path B-Galactic
        //Blue
        new IntakePowerCell(),
        new MoveToCoordinate(150, 0),
        new IntakePowerCell(),
        new MoveToCoordinate(210, -60),
        new IntakePowerCell(),
        new MoveToCoordinate(270, 0),
        new MoveToCoordinate(340, 0),
    }));
    break;

  default:
  break;
}
}

// Called repeatedly when this Command is scheduled to run
void AutoChallengeChooser::Execute() {}

// Called once the command ends or is interrupted.
void AutoChallengeChooser::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoChallengeChooser::IsFinished() {
  return false;
}
