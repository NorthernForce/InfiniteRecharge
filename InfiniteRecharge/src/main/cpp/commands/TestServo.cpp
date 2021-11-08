// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TestServo.h"
#include "RobotContainer.h"

TestServo::TestServo() {
  AddRequirements(RobotContainer::cameraMount.get());
}

// Called when the command is initially scheduled.
void TestServo::Initialize() {
    if (RobotContainer::cameraMount->GetCurrentPan() < 0)
        RobotContainer::cameraMount->Pan(90);
    else
        RobotContainer::cameraMount->Pan(-90);
    RobotContainer::cameraMount->ResumeSweep();
}

// Called repeatedly when this Command is scheduled to run
void TestServo::Execute() {
    RobotContainer::cameraMount->Sweep();
}

// Called once the command ends or is interrupted.
void TestServo::End(bool interrupted) {}

// Returns true when the command should end.
bool TestServo::IsFinished() {
  return false;
}
