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
std::shared_ptr<DriveShifter> RobotContainer::driveShifter;
std::shared_ptr<PCM> RobotContainer::pcm;
std::shared_ptr<IMU> RobotContainer::imu;
std::shared_ptr<Navigation> RobotContainer::navigation;
std::shared_ptr<CameraMount> RobotContainer::cameraMount;
// std::shared_ptr<AIVisionTargetting> RobotContainer::aiVisionTargetting;
std::shared_ptr<Ultrasonic> RobotContainer::ultrasonic;
std::shared_ptr<Intake> RobotContainer::intake;
std::shared_ptr<Shooter> RobotContainer::shooter;
std::shared_ptr<Climber> RobotContainer::climber;

RobotContainer::RobotContainer() {
  oi.reset(new OI());
  InitSubsystems();
  InitDefaultCommands();
  oi->MapControllerButtons();
}

void RobotContainer::InitSubsystems() {
  drivetrain.reset(new Drivetrain);
  pcm.reset(new PCM);
  driveShifter.reset(new DriveShifter);
  imu.reset(new IMU);
  navigation.reset(new Navigation);
  // aiVisionTargetting.reset(new AIVisionTargetting);
  cameraMount.reset(new CameraMount);
  ultrasonic.reset(new Ultrasonic);
  intake.reset(new Intake);
  shooter.reset(new Shooter);
  climber.reset(new Climber);
}

void RobotContainer::InitDefaultCommands() {
  drivetrain->SetDefaultCommand(DriveWithJoystick(
    [this] { return oi->driverController->GetY(frc::XboxController::kLeftHand); },
    [this] { return oi->driverController->GetX(frc::XboxController::kRightHand) *-1; }
  ));

  climber->SetDefaultCommand(Climb( 
    [this] { return oi->manipulatorController->GetY(frc::XboxController::kLeftHand); }
  ));
}