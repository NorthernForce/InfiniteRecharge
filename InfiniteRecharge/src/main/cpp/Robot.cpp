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
#include "commands/autonomous/SimpleCrossAutoLine.h"
#include "subsystems/DriveShifter.h"

#include <cameraserver/CameraServer.h>

void Robot::RobotInit() {
  container.reset(new RobotContainer());
////TODO: Fix the autonomous stuff because sendablechooser is annoying and I don't understand it
/*
  autonomousChooser.SetDefaultOption("1) Cross auto line", new CrossAutoLine());
  autonomousChooser.AddOption("2) In front of goal", new InFrontOfGoal());
  autonomousChooser.AddOption("3) In front of our trench", new InFrontOfOurTrench());
  autonomousChooser.AddOption("4) In front of foe's trench", new InFrontOfFoesTrench());
  autonomousChooser.AddOption("4) Do Nothing", new DoNothing());
  frc::SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);
*/
  chooserAuto = new frc::SendableChooser<std::string>;
  chooserAuto->SetDefaultOption("Chooser::Auto::DoNothing", "DoNothing");
  chooserAuto->AddOption("Chooser::Auto::CrossAutoLine", "CrossAutoLine");
  chooserAuto->AddOption("Chooser::Auto::InFrontOfGoal", "InFrontOfGoal");
  chooserAuto->AddOption("Chooser::Auto::SimpleCrossAutoLine", "SimpleCrossAutoLine");
  chooserAuto->AddOption("Chooser::Auto::InFrontOfOurTrench", "InFrontOfOurTrench");
  chooserAuto->AddOption("Chooser::Auto::InFrontOfFoesTrench", "InFrontOfFoesTrench");
  frc::SmartDashboard::PutData(chooserAuto);

  CameraServer::GetInstance()->StartAutomaticCapture();
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
SimpleDriveForward = new SimpleCrossAutoLine();
/*
	autonomousCommand.reset(autonomousChooser.GetSelected());
  if(autonomousCommand != nullptr)
      autonomousCommand->Schedule();
*/
////TODO: Figure out if this should go in periodic or Init
  /*
  chooserAutoSelected = chooserAuto->GetSelected();

        if (chooserAutoSelected == "CrossAutoLine") {
        new CrossAutoLine;
    }
    else if (chooserAutoSelected == "DoNothing") {
       new DoNothing;
    }
    else if (chooserAutoSelected == "InFrontOfGoal") {
       new InFrontOfGoal;
    }
    else if (chooserAutoSelected == "InFrontOfFoesTrench") {
      new InFrontOfFoesTrench;
    }
    else if (chooserAutoSelected == "InFrontOfOurTrench") {
      new InFrontOfOurTrench;
    }
    else {
      new DoNothing;
    }
*/
  RobotContainer::drivetrain->SetEncoderPosition(0);
}


void Robot::AutonomousPeriodic() {
  if (!SimpleDriveForward->IsScheduled()) {
        SimpleDriveForward->Schedule();
      }
      
  /*
  auto encoderRotations = RobotContainer::drivetrain->GetEncoderRotations();
  RobotContainer::drivetrain->DriveUsingSpeeds(0.2, 0.2);
  if (((encoderRotations.second)*Constants::Shifting::highMultiplier) > 35)
    RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
  */

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

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
