/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <thread>

#include "RobotContainer.h"
#include "utilities/AutoCommandScheduler.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  static void CameraInit();
  
  bool AutonomousIsRunning = false;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.

  std::shared_ptr<RobotContainer> container;
  //std::unique_ptr<frc2::Command> autonomousCommand;
  //frc::SendableChooser<frc2::Command*> autonomousChooser;
  //frc::SendableChooser<std::string> *chooserAuto;
  //SimpleCrossAutoLine* simpleDriveForward;
  //MoveToLimelight* autoMoveToLimelight;
  //AutoDrive* autoDrive;
  //std::shared_ptr<TurnToAngle> autoTurnToAngle;
  //std::shared_ptr<SimpleCrossAutoLine> simpleCrossAutoLine;
  //std::shared_ptr<CrossAutoLine> autoTestDrive;
  //ShootCell* autoShooter;
  //std::string chooserAutoSelected;
  std::unique_ptr<AutoCommandScheduler> autoCommandScheduler;

  bool reachedEncoderPos = false;
  bool readyToShoot = false;
  int autoCounter;
};
