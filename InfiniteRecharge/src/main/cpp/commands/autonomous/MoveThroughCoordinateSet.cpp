/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/autonomous/MoveThroughCoordinateSet.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/autonomous/MoveToCoordinate.h"

MoveThroughCoordinateSet::MoveThroughCoordinateSet() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void MoveThroughCoordinateSet::Initialize() {
  // coordinateSet = std::vector<CPlane::Point>{CPlane::C1, CPlane::C3, CPlane::D6, CPlane::E5, CPlane::D4, CPlane::B9, CPlane::A8, CPlane::B7, CPlane::D9, CPlane::E10, CPlane::D11, CPlane::C9, CPlane::C1};
  coordinateSet = std::vector<CPlane::Point>{CPlane::Point(70,0)};
  obstacles = std::vector<CPlane::Point>{CPlane::Point(35,5)};
  numOfSets = coordinateSet.size() / 2;
  status = 0; 
}

// Called repeatedly when this Command is scheduled to run
void MoveThroughCoordinateSet::Execute() {
  //checks to make sure there is another set of coordinates
  if (status != numOfSets + 1) {
    //move robot to that coordinates
   // MoveToCoordinate(coordinateSet.at(xPos), coordinateSet.at(yPos));
   //is this good here? can they be nested this way?
    if (!avoidObstacles->IsScheduled()) {
      avoidObstacles.reset(new AvoidObstacles(coordinateSet[status], obstacles, 0.13));
      avoidObstacles->Schedule();
      status++;
    }
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
