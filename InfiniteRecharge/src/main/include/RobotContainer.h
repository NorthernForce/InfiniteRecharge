/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include "OI.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/PCM.h"
#include "subsystems/DriveShifter.h"
#include "subsystems/IMU.h"
#include "subsystems/Navigation.h"
#include "subsystems/CameraMount.h"
#include "subsystems/AIVisionTargetting.h"
#include "subsystems/Ultrasonic.h"

#include "commands/DriveWithJoystick.h"
#include "utilities/Communications.h"

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
  static std::shared_ptr<OI> oi;
  static std::shared_ptr<Drivetrain> drivetrain;
  static std::shared_ptr<PCM> pcm;
  static std::shared_ptr<DriveShifter> driveShifter;
  static std::shared_ptr<IMU> imu;
  static std::shared_ptr<Navigation> navigation;
  // static std::shared_ptr<AIVisionTargetting> aiVisionTargetting;
  static std::shared_ptr<CameraMount> cameraMount;
  static std::shared_ptr<Ultrasonic> ultrasonic;

  static std::shared_ptr<SocketHandler> aiComms;

 private:
  void InitSubsystems();
  void InitDefaultCommands();
};
