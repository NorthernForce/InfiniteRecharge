/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "RobotContainer.h"

AutoDrive::AutoDrive(double inches, double leftSpeed, double rightSpeed)
 : m_inches(inches), m_leftSpeed(leftSpeed), m_rightSpeed(rightSpeed) {
  AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void AutoDrive::Initialize() {
  CheckForAndFixNegatives();
}

void AutoDrive::CheckForAndFixNegatives() {
  if (m_inches < 0) {
    m_inches *= -1;
    m_rightSpeed *= -1;
    m_leftSpeed *= -1;
  }
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
  bool obstacle = RobotContainer::ultrasonic->IsObstacleAt(12);
  double encoderToTravel = m_inches * Constants::Shifting::highMultiplier;
  double averageDistance = (RobotContainer::drivetrain->GetEncoderRotations().first + RobotContainer::drivetrain->GetEncoderRotations().second)/2;

  if(!obstacle && (averageDistance < encoderToTravel))
      RobotContainer::drivetrain->DriveUsingSpeeds(m_leftSpeed, m_rightSpeed);
  else if (obstacle && (averageDistance < encoderToTravel))
      RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
  else {
      RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
      IsFinished();
  }
}

// Called once the command ends or is interrupted.
void AutoDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoDrive::IsFinished() { return true; }