/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoystick.h"
#include "commands/ShiftGear.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/Drivetrain.h"

int DriveWithJoystick::countForShiftEligibility;

DriveWithJoystick::DriveWithJoystick() {
  SetName("DriveWithJoystick");
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());
}

// Called when the command is initially scheduled.
void DriveWithJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  auto driveControls = RobotContainer::oi->GetDriveControls();
  speed = driveControls.first;
  rotation = driveControls.second;
  RobotContainer::drivetrain->Drive(speed, rotation);

  AutoShiftIfPermitted();
}

// Called once the command ends or is interrupted.
void DriveWithJoystick::End(bool interrupted) {
  RobotContainer::drivetrain->Drive(0, 0);
}

// Returns true when the command should end.
bool DriveWithJoystick::IsFinished() { return false; }

void DriveWithJoystick::AutoShiftIfPermitted() {
  double positiveAcceleration = abs(RobotContainer::imu->GetAcceleration());
  bool isEligibleForShift;

  if (positiveAcceleration > 0.1 && countForShiftEligibility >= 25)
    isEligibleForShift = true;

  if (isEligibleForShift) {
    ShiftIfEligible(isEligibleForShift);
  }
  countForShiftEligibility++;
}

void DriveWithJoystick::ShiftIfEligible(bool isEligible) {
  bool isDrivingStraight = (speed > 0.75 && abs(rotation) < 0.15);
  if (isDrivingStraight && RobotContainer::imu->IsMoreTorqueNeeded() == true)
    ShiftGear(ShiftGear::Gear::Low);
  else
    ShiftGear(ShiftGear::Gear::High);
  countForShiftEligibility = 0;
}