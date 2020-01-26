/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"

std::shared_ptr<frc::XboxController> RobotContainer::driverController;
std::shared_ptr<frc::XboxController> RobotContainer::manipulatorController;

std::shared_ptr<Drivetrain> RobotContainer::drivetrain;
std::shared_ptr<PCM> RobotContainer::pcm;

RobotContainer::RobotContainer() {
  InitSubsystems();

  InitControllers();
  InitDefaultCommands();
  
  ConfigureButtonBindings();
}

void RobotContainer::InitControllers() {
  driverController.reset(new frc::XboxController(Constants::OI::driverController_id));
  manipulatorController.reset(new frc::XboxController(Constants::OI::manipulatorController_id));
}

void RobotContainer::InitSubsystems() {
  drivetrain.reset(new Drivetrain);
  pcm.reset(new PCM);
}

void RobotContainer::InitDefaultCommands() {
  drivetrain->SetDefaultCommand(DriveWithJoystick(
    [this] { return driverController->GetY(frc::XboxController::kLeftHand); },
    [this] { return driverController->GetX(frc::XboxController::kRightHand); }
  ));
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}


double RobotContainer::getDriveSpeedMultiplier() {
  double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed: ", 1.0);
  if (speedMultiplier < 0)
      speedMultiplier = 0;
  else if (speedMultiplier > 1)
      speedMultiplier = 1;

  return speedMultiplier;
}