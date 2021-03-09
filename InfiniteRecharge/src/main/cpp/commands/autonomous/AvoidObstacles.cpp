// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AvoidObstacles.h"

AvoidObstacles::AvoidObstacles(double xPos, double yPos, std::vector<CPlane::Point> obstacles, double speed) {
moveToCoordinate = std::make_unique<MoveToCoordinate>(xPos, yPos, speed);
obstacleList = obstacles;
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AvoidObstacles::Initialize() {} 

auto AvoidObstacles::NearestGameCoordinate() {
  CPlane::Point point = CPlane::Point((round(robot.x/30)*30),(round(robot.y/30)*30));
  return point;
}

void AvoidObstacles::UpdatePosition() {
  auto coordinates = RobotContainer::navigation->GetCoordinatePosition();
  robot = CPlane::Point(coordinates.first,coordinates.second);
  ngc = NearestGameCoordinate();
}

double AvoidObstacles::NGCAngle() {
  return RobotContainer::navigation->AngleToPoint(ngc.x, ngc.y);
}

double AvoidObstacles::NGCDistance() {
  return sqrt(pow((robot.x - ngc.x),2) + pow((robot.y - ngc.y),2));
}

bool AvoidObstacles::WillHitNGC() {
  double horizontalDistance = NGCDistance() * sin(NGCAngle());
  return (horizontalDistance < Constants::obstacleDistance);
}

bool AvoidObstacles::NGCisObstacle() {
  for(auto element : obstacleList) {
    if ((element.x == ngc.x) && (element.y == ngc.y)) {return true;}
  }
  return false;
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
  if (WillHitNGC() && NGCisObstacle()) { //If it will pass through a point checks if it is an obstacle    
    moveToCoordinate->AvoidRedirection(CorrectionAmount());
  }
}

// Called once the command ends or is interrupted.
void AvoidObstacles::End(bool interrupted) {
  moveToCoordinate->Cancel();
}

// Returns true when the command should end.
bool AvoidObstacles::IsFinished() {
  return (!moveToCoordinate->IsScheduled());
}
