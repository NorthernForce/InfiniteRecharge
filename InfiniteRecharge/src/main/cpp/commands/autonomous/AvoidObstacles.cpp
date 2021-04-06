// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AvoidObstacles.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <cmath>

AvoidObstacles::AvoidObstacles(CPlane::Point end, std::vector<CPlane::Point> obstacles, double speed) {
moveToCoordinate = std::make_unique<MoveToCoordinate>(end, speed);
obstacleList = obstacles;
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AvoidObstacles::Initialize() {
  moveToCoordinate->Schedule();
} 

auto AvoidObstacles::NearestObstacle() { //Each call iterates through list of obstacle, updates after every full cycle
  if (obstacleList.size() == 1) {
    obstacle = obstacleList[0];
  }
  else {
    CPlane::Point tempObstacle = obstacleList[obstacleListIndex];
    tempObstacle.distance = sqrt(pow((robot.x - tempObstacle.x),2) + pow((robot.y - tempObstacle.y),2));

    bool tempIsCloser = (tempObstacle.distance < newObstacle.distance);

    bool tempInFOV = (abs(RobotContainer::navigation->AngleToPoint(tempObstacle.x,tempObstacle.y)) < obstacleFOV);
    if (tempIsCloser && tempInFOV) {
      newObstacle = tempObstacle;
    }
    if (obstacleListIndex >= (int)obstacleList.size()) {
      obstacle = newObstacle;
      obstacleListIndex = 0;
      newObstacle.distance = 1000;
    }
  }
}

void AvoidObstacles::UpdatePosition() {
  auto coordinates = RobotContainer::navigation->GetCoordinatePosition();
  robot = CPlane::Point(coordinates.first,coordinates.second);
}

double AvoidObstacles::ObstacleAngle() {
  return RobotContainer::navigation->AngleToPoint(obstacle.x, obstacle.y);
}

bool AvoidObstacles::WillHitObstacle() {
  double horizontalDistance = obstacle.distance * sin(ObstacleAngle());
  return (abs(horizontalDistance) < Constants::obstacleDistance);
}

double AvoidObstacles::CorrectionAmount() {
  double angleCorrection = abs(asin(Constants::obstacleDistance/obstacle.distance)) / Constants::degreesToRadians - abs(ObstacleAngle());
  frc::SmartDashboard::PutNumber("absObstacleOffset: ",abs(ObstacleAngle()));
  frc::SmartDashboard::PutNumber("angleCorrection", angleCorrection);
  frc::SmartDashboard::PutNumber("obsacleSize: ", abs(asin(Constants::obstacleDistance/obstacle.distance)) / Constants::degreesToRadians);
  if (angleCorrection > 0) {
    if (ObstacleAngle() > 0) {
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
  if (obstacleList.size()) {

    UpdatePosition();
    if (WillHitObstacle()) {
      moveToCoordinate->AvoidRedirection(CorrectionAmount());
    }

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
