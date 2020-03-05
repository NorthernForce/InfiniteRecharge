/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <cameraserver/CameraServer.h>
#include <string>

#include "Constants.h"
#include "OI.h"

#include "commands/InventoryPowerCells.h"
#include "commands/autonomous/CrossAutoLine.h"
#include "commands/autonomous/InFrontOfGoal.h"
#include "commands/autonomous/InFrontOfOurTrench.h"
#include "commands/autonomous/InFrontOfFoesTrench.h"
#include "commands/autonomous/DoNothing.h"

#include <opencv2/opencv.hpp>


void Robot::RobotInit() {
  container.reset(new RobotContainer());

  autonomousChooser.SetDefaultOption("1) Cross auto line", new CrossAutoLine());
  autonomousChooser.AddOption("2) In front of goal", new InFrontOfGoal());
  autonomousChooser.AddOption("3) In front of our trench", new InFrontOfOurTrench());
  autonomousChooser.AddOption("4) In front of foe's trench", new InFrontOfFoesTrench());
  autonomousChooser.AddOption("4) Do Nothing", new DoNothing());
  frc::SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);

  cameraThread.reset(new std::thread(CameraInit));
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
	autonomousCommand.reset(autonomousChooser.GetSelected());
  if(autonomousCommand != nullptr)
      autonomousCommand->Schedule();
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

void Robot::CameraInit() {
  cv::Mat frame;
  cv::VideoCapture cap;
  int deviceID = 0;

  cap.open(deviceID);
  if (!cap.isOpened()) {
      std::cerr << "ERROR! Unable to open camera\n";
  }
  for (;;)
  {
      cap.read(frame);
      if (frame.empty()) {
          std::cerr << "ERROR! blank frame grabbed\n";
          break;
      }

      cv::imshow("Live", frame);
      if (cv::waitKey(5) >= 0)
          break;
  }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
