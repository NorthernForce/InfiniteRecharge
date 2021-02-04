// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AvoidObstacles.h"

AvoidObstacles::AvoidObstacles() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AvoidObstacles::Initialize() {}

bool AvoidObstacles::TestForCollision(double xTarget, double yTarget) {
  auto coordinates = RobotContainer::navigation->GetCoordinatePosition();
  double xCurrent = coordinates.first;
  double yCurrent = coordinates.second;
  auto point = std::make_pair(round(xCurrent/30)*30,round(yCurrent/30)*30);
  
  return (sqrt(pow((xCurrent - point.first),2) + pow((xCurrent - point.second),2)) < Constants::robotRadius);
}


// Called repeatedly when this Command is scheduled to run
void AvoidObstacles::Execute() {}

// Called once the command ends or is interrupted.
void AvoidObstacles::End(bool interrupted) {}

// Returns true when the command should end.
bool AvoidObstacles::IsFinished() {
  return false;
}
