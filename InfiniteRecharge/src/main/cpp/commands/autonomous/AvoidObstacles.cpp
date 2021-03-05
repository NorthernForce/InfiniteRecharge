// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AvoidObstacles.h"

AvoidObstacles::AvoidObstacles(double xPos, double yPos, double speed, std::vector<CPlane::Point> obstacles) {
moveToCoordinate = std::make_unique<MoveToCoordinate>(xPos, yPos, speed);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AvoidObstacles::Initialize() {} 

auto AvoidObstacles::NearestGameCoordinate() {
  auto point = std::make_pair(round(xCurrent/30)*30,round(yCurrent/30)*30);
  return point;
}

void AvoidObstacles::UpdatePosition() {
  auto coordinates = RobotContainer::navigation->GetCoordinatePosition();
  xCurrent = coordinates.first;
  yCurrent = coordinates.second;
  ngc = NearestGameCoordinate();
}

double AvoidObstacles::NGCAngle() {
  return RobotContainer::navigation->AngleToPoint(ngc.first, ngc.second);
}

double AvoidObstacles::NGCDistance() {
  return sqrt(pow((xCurrent - ngc.first),2) + pow((xCurrent - ngc.second),2));
}

bool AvoidObstacles::WillHitNGC() {
  double horizontalDistance = NGCDistance() * sin(NGCAngle());
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
void AvoidObstacles::End(bool interrupted) {
  moveToCoordinate->Cancel();
}

// Returns true when the command should end.
bool AvoidObstacles::IsFinished() {
  return (!moveToCoordinate->IsScheduled());
}
