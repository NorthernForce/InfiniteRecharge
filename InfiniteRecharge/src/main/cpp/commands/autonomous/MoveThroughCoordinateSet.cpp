/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/MoveThroughCoordinateSet.h"
#include "frc/smartdashboard/SmartDashboard.h"

MoveThroughCoordinateSet::MoveThroughCoordinateSet() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void MoveThroughCoordinateSet::Initialize() {
  coordinateSet = frc::SmartDashboard::GetNumberArray(coordinateSetLabel, -1);
  numOfSets = coordinateSet.size() / 2;
  xPos = 0;
  yPos = 1;
}

// Called repeatedly when this Command is scheduled to run
void MoveThroughCoordinateSet::Execute() {
  //checks to make sure there is another set of coordinates
  if (status != numOfSets + 1) {
    //move robot to that coordinates
    MoveToCoordinate(coordinateSet.at(xPos), coordinateSet.at(yPos));
    status++;
    xPos += 2;
    yPos += 2;
  }
}

// Called once the command ends or is interrupted.
void MoveThroughCoordinateSet::End(bool interrupted) {}

// Returns true when the command should end.
bool MoveThroughCoordinateSet::IsFinished() { 
  if (status == numOfSets + 1) {
    return true;
  }
  else {
    return false;
  }
}
