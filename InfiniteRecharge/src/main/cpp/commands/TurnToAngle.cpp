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

double TurnToAngle::targetAngle;

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
  currentAngle = RobotContainer::imu->GetRotation();
  totalTargetAngle = currentAngle + targetAngle;
  integral = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnToAngle::Execute() {
  double p = frc::SmartDashboard::GetNumber("TurnToAngle: P", pValue);
  double i = frc::SmartDashboard::GetNumber("TurnToAngle: I", iValue);
  double d = frc::SmartDashboard::GetNumber("TurnToAngle: D", dValue);

  double rotationRaw = GetRotationFromPID(p,i,d);
  double rotationLimited = LimitMaxTurnSpeed(rotationRaw);
  std::cout << "rotlim: " << rotationLimited << "\n";
  
  auto driveControls = RobotContainer::oi->GetDriveControls();
  RobotContainer::drivetrain->Drive(driveControls.first, rotationLimited + driveControls.second * 0.5);
}

void TurnToAngle::End(bool interrupted) {
  RobotContainer::drivetrain->Drive(0,0);
}

bool TurnToAngle::CheckIfFinished() {
  if ((targetAngle >= 0) && (currentAngle >= targetAngle))
    return true;
  else if ((targetAngle <= 0) && (currentAngle <= targetAngle))
    return true;
  else if (std::abs(error) < minError)
    return true;
  else
    return false;
}

bool TurnToAngle::IsFinished() {
  if (std::abs(error) < minError)
    return true;
  else
    return false;  
}

double TurnToAngle::GetRotationFromPID(double p, double i, double d) {
  error = (RobotContainer::imu->GetRotation() - totalTargetAngle) / 180;
  if (error == 0)
    integral = 0;

  integral += error * defaultPeriodInMs;
  derivative = (error - errorPrior) / defaultPeriodInMs;
  double rotation = p*error + i*integral + d*derivative;
  errorPrior = error;
  return rotation;
}

double TurnToAngle::LimitMaxTurnSpeed(double currentSpeed) {
  double speed = currentSpeed;
  if (currentSpeed < maxTurnSpeed * -1)
    speed = maxTurnSpeed * -1;
  else if (currentSpeed > maxTurnSpeed)
    speed = maxTurnSpeed;
  return speed;
}