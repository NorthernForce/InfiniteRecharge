/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
    AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void DriveWithJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  std::pair<double, double> steeringControls = RobotContainer::oi->getSteeringControls();
  RobotContainer::drivetrain->Drive(steeringControls.first, steeringControls.second);
}

// Called once the command ends or is interrupted.
void DriveWithJoystick::End(bool interrupted) {
////TODO: Review whether we want to stop the Drive if this is just Interrupted, If (interrupted == false) ...///
  RobotContainer::drivetrain->Drive(0, 0);
}

// Returns true when the command should end.
bool DriveWithJoystick::IsFinished() { return false; }
