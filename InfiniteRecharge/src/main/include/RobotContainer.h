/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/PCM.h"

#include "commands/DriveWithJoystick.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();
  static std::shared_ptr<Drivetrain> drivetrain;
  static std::shared_ptr<PCM> pcm;
  static double getDriveSpeedMultiplier();

 private:
  // The robot's subsystems and commands are defined here...
  void InitSubsystems();
  void InitControllers();
  void InitDefaultCommands();
  void ConfigureButtonBindings();
  static std::shared_ptr<frc::XboxController> driverController;
  static std::shared_ptr<frc::XboxController> manipulatorController;

};
