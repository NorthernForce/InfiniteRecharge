/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToAngle.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/TimedRobot.h>
#include "RobotContainer.h"

TurnToAngle::TurnToAngle(double target) {
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::imu.get());

  targetAngle = target;

  frc::SmartDashboard::PutNumber("TurnToAngle: P", pValue);
  frc::SmartDashboard::PutNumber("TurnToAngle: I", iValue);
  frc::SmartDashboard::PutNumber("TurnToAngle: D", dValue);
}

// Called when the command is initially scheduled.
void TurnToAngle::Initialize() {
  RobotContainer::imu->ZeroRotation();
  totalTargetAngle = RobotContainer::imu->GetRotation() + targetAngle;
  integral = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnToAngle::Execute() {
  double p = frc::SmartDashboard::GetNumber("TurnToAngle: P", pValue);
  double i = frc::SmartDashboard::GetNumber("TurnToAngle: I", iValue);
  double d = frc::SmartDashboard::GetNumber("TurnToAngle: D", dValue);

  // PID Loop math taken from some site on the internet
  error = (RobotContainer::imu->GetRotation() - totalTargetAngle) / 180;
  if (error == 0)
    integral = 0;

  integral += error * defaultPeriodInMs;
  derivative = (error - errorPrior) / defaultPeriodInMs;
  double rotation = p*error + i*integral + d*derivative;
  errorPrior = error;

  // Limit max turn speed
  if (rotation < maxTurnSpeed * -1) {
    rotation = maxTurnSpeed * -1;
  }
  else if (rotation > maxTurnSpeed) {
    rotation = maxTurnSpeed;
  }
  std::cout << " rotation: " << rotation << " goal: " << totalTargetAngle << " angle: " << RobotContainer::imu->GetRotation() << '\n';

  auto driveControls = RobotContainer::oi->GetDriveControls();
  RobotContainer::drivetrain->Drive(driveControls.first, rotation + driveControls.second * 0.5);
}

// Called once the command ends or is interrupted.
void TurnToAngle::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToAngle::IsFinished() { return false; }
