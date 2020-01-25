/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoystick.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/Drivetrain.h"

DriveWithJoystick::DriveWithJoystick(std::function<double()> speed, std::function<double()> rotation)
  :  m_speed(speed), m_rotation(rotation) {
    SetName("DriveWithJoystick");
    AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void DriveWithJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  double speedMultiplier = RobotContainer::getSpeedMultiplier();
  RobotContainer::drivetrain->Drive(m_speed() * speedMultiplier, m_rotation() * speedMultiplier);
}

// Called once the command ends or is interrupted.
void DriveWithJoystick::End(bool interrupted) {
////TODO: Review whether we want to stop the Drive if this is just Interrupted, If (interrupted == false) ...///
  RobotContainer::drivetrain->Drive(0, 0);
}

// Returns true when the command should end.
bool DriveWithJoystick::IsFinished() { return false; }