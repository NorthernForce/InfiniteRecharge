/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SweepAICamera.h"
#include <iostream>
#include <functional>
#include <future>

SweepAICamera::SweepAICamera() {
  AddRequirements(RobotContainer::cameraMount.get());
}

// Called when the command is initially scheduled.
void SweepAICamera::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SweepAICamera::Execute() {
  std::cout << "running sweep command\n";
  std::future<bool> awaitSweep = std::async(RobotContainer::cameraMount->IntervaledExecution, RobotContainer::cameraMount->SweepForPowercells, 10);
  awaitSweep.get();
  //Query AI for Powercell in frame
  /*
  if(!TargFound)
  {
    RobotContainer::cameraMount->SweepForPowercells();
  }
  else
  {
    End(true);
  }
  */
}

// Called once the command ends or is interrupted.
void SweepAICamera::End(bool interrupted) {}

// Returns true when the command should end.
bool SweepAICamera::IsFinished() { return true; }
