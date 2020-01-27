/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>
#include "Constants.h"

std::shared_ptr<OI> RobotContainer::oi;
std::shared_ptr<Drivetrain> RobotContainer::drivetrain;
std::shared_ptr<PCM> RobotContainer::pcm;

RobotContainer::RobotContainer() {
  InitSubsystems();

  oi.reset(new OI);
  oi->InitControllers();

  oi->MapControllerButtons();
  InitDefaultCommands();
}

void RobotContainer::InitSubsystems() {
  drivetrain.reset(new Drivetrain);
  pcm.reset(new PCM);
}

void RobotContainer::InitDefaultCommands() {
  drivetrain->SetDefaultCommand(DriveWithJoystick(
    [this] { return oi->driverController->GetY(frc::XboxController::kLeftHand); },
    [this] { return oi->driverController->GetX(frc::XboxController::kRightHand); }
  ));
}