// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AvoidObstacles.h"

std::shared_ptr<MoveToCoordinate> moveToCoordinate;

AvoidObstacles::AvoidObstacles() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AvoidObstacles::Initialize() {}

auto AvoidObstacles::NearestGameCoordinate() {
  return std::make_pair(round(xCurrent/30)*30,round(yCurrent/30)*30); 
}

void AvoidObstacles::UpdatePosition() {
  auto coordinates = RobotContainer::navigation->GetCoordinatePosition();
  xCurrent = coordinates.first;
  yCurrent = coordinates.second;
  ngc = NearestGameCoordinate();
  horizontalDistance= NGCDistance() * sin(NGCAngle() * Constants::degreesToRadians);
}

double AvoidObstacles::NGCAngle() {
  return RobotContainer::navigation->AngleToPoint(ngc.first, ngc.second);
}

double AvoidObstacles::NGCDistance() {
  return sqrt(pow((xCurrent - ngc.first),2) + pow((xCurrent - ngc.second),2));
}

bool AvoidObstacles::WillHitNGC() {
  return (horizontalDistance < Constants::obstacleDistance);
}

double AvoidObstacles::CorrectionAmount() {
  double horizontalCorrection = Constants::obstacleDistance - horizontalDistance;
  if (horizontalCorrection > 0) {
    double angleCorrection = asin(horizontalCorrection/NGCDistance()) / Constants::degreesToRadians;
    if (NGCAngle() > 0) {
      return angleCorrection;
    }
    else {
      return -angleCorrection;
    }
  }
  else {
    return 0;
  }
}

// Called repeatedly when this Command is scheduled to run
void AvoidObstacles::Execute() {
  UpdatePosition();
  moveToCoordinate->AvoidRedirection(CorrectionAmount()); 
}

// Called once the command ends or is interrupted.
void AvoidObstacles::End(bool interrupted) {}

// Returns true when the command should end.
bool AvoidObstacles::IsFinished() {
  return !moveToCoordinate->IsScheduled();
}
 