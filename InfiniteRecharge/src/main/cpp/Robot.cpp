/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <cameraserver/CameraServer.h>
#include <string>
#include <memory>

#include "Constants.h"
#include "OI.h"

#include "commands/InventoryPowerCells.h"
#include "commands/autonomous/AutoShootCell.h"
#include "commands/autonomous/SimpleCrossAutoLine.h"
#include "subsystems/DriveShifter.h"
#include "commands/AutoDrive.h"
#include "commands/ShiftGear.h"
#include "commands/SafeCamera.h"
#include "commands/TurnToAngle.h"
#include "commands/ShootCell.h"
#include "commands/MoveToLimelight.h"
#include "commands/autonomous/AutoBallSeek.h"

#include <cameraserver/CameraServer.h>
#include <frc2/command/ParallelCommandGroup.h>


void Robot::RobotInit() {
    container = std::make_shared<RobotContainer>();

    frc::SmartDashboard::PutString("auto string input 1", "insert here");
    frc::SmartDashboard::PutNumber("auto 1 parameter", 0);
    frc::SmartDashboard::PutString("auto string input 2", "insert here");
    frc::SmartDashboard::PutNumber("auto 2 parameter", 0);
    frc::SmartDashboard::PutString("auto string input 3", "insert here");
    frc::SmartDashboard::PutNumber("auto 3 parameter", 0);
    frc::SmartDashboard::PutString("auto string input 4", "insert here");
    frc::SmartDashboard::PutNumber("auto 4 parameter", 0);
    frc::SmartDashboard::PutString("auto string input 5", "insert here");
    frc::SmartDashboard::PutNumber("auto 5 parameter", 0);


    ////TODO: Fix the autonomous stuff because sendablechooser is annoying and I don't understand it
    /*
    autonomousChooser.SetDefaultOption("1) Cross auto line", new CrossAutoLine());
    autonomousChooser.AddOption("2) In front of goal", new InFrontOfGoal());
    autonomousChooser.AddOption("3) In front of our trench", new InFrontOfOurTrench());
    autonomousChooser.AddOption("4) In front of foe's trench", new InFrontOfFoesTrench());
    autonomousChooser.AddOption("4) Do Nothing", new DoNothing());
    frc::SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);
    */
    /*

    chooserAuto = new frc::SendableChooser<std::string>;
    chooserAuto->SetDefaultOption("DoNothing", "DoNothing");
    chooserAuto->AddOption("CrossAutoLine", "CrossAutoLine");
    chooserAuto->AddOption("InFrontOfGoal", "InFrontOfGoal");
    chooserAuto->AddOption("SimpleCrossAutoLine", "SimpleCrossAutoLine");
    chooserAuto->AddOption("InFrontOfOurTrench", "InFrontOfOurTrench");
    chooserAuto->AddOption("InFrontOfFoesTrench", "InFrontOfFoesTrench");
    frc::SmartDashboard::PutData(chooserAuto);

    */

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

    //   frc2::SequentialCommandGroup{
    //   TurnToAngle(90),
    //   SimpleCrossAutoLine(),
    // };


    // Aiden's stuff
    // autoTurnToAngle.reset(new TurnToAngle);
    //simpleCrossAutoLine.reset(new SimpleCrossAutoLine);
    //autoShootCell.reset(new AutoShootCell);

    // RobotContainer::drivetrain->SetEncoderPosition(0);
    //autoTurnToAngle->SetAngle(90);
    // isTurnFinished = false;
    // isForwardFinished = false;
    // isShooterFinished = false;

    // auto command scheduler init
    // autoCommandScheduler.reset(new AutoCommandScheduler({
    //     new AutoBallSeek()
    // }));

}


void Robot::AutonomousPeriodic() {

    // auto command scheduler execution
    //autoCommandScheduler->RunSequential();
 
/*

if(isTurnFinished == false) {
  autoTurnToAngle->Schedule();
  isTurnFinished = true;
   } else if((!autoTurnToAngle->IsScheduled()) && (isForwardFinished == false) && (isTurnFinished == true)) {
       simpleCrossAutoLine->Schedule();
       isForwardFinished = true;
   } else if ((!simpleCrossAutoLine->IsScheduled()) && (isShooterFinished == false) && (isForwardFinished == true)) {
     std::cout << "I should be shooting a ball rn \n";
     autoShootCell->Schedule();
     isShooterFinished = true;
   }
*/


if(autoStepOne == false) {
  std::string autoOneString = frc::SmartDashboard::GetString("auto string input 1", "insert here");
  int autoOneNum = frc::SmartDashboard::GetNumber("auto 1 parameter", 0);
  RobotContainer::drivetrain->SetEncoderPosition(0);

  if((autoOneString == "Turn") && (!autoTurnToAngle->IsScheduled()) && (autoPointOne == false)) {
    
    autoTurnToAngle.reset(new TurnToAngle);
    autoTurnToAngle->SetAngle(autoOneNum);
    autoTurnToAngle->Schedule();
    autoPointOne = true;

    } else if ((autoOneString == "GoForward") && (!simpleCrossAutoLine->IsScheduled()) && (autoPointOne == false)) {

      simpleCrossAutoLine.reset(new SimpleCrossAutoLine);
      simpleCrossAutoLine->SetDistance(autoOneNum);
      simpleCrossAutoLine->Schedule();
      autoPointOne = true;

    } else if (autoOneString == "Shoot") {

      autoShootCell.reset(new AutoShootCell);
      autoShootCell->Schedule();
      autoPointOne = true;

    } else {
      autoStepOne = true;
    }
}

if ((autoStepTwo == false) && (autoStepOne == true)) {
    std::string autoTwoString = frc::SmartDashboard::GetString("auto string input 2", "insert here");
    int autoTwoNum = frc::SmartDashboard::GetNumber("auto 2 parameter", 0);

    if((autoTwoString == "Turn") && (!autoTurnToAngle->IsScheduled()) && (!simpleCrossAutoLine->IsScheduled()) && (autoPointTwo == false)) {

    RobotContainer::drivetrain->SetEncoderPosition(0);
    autoTurnToAngle.reset(new TurnToAngle);
    autoTurnToAngle->SetAngle(autoTwoNum);
    autoTurnToAngle->Schedule();
    autoPointTwo = true;

    } else if ((autoTwoString == "GoForward") && (!simpleCrossAutoLine->IsScheduled()) && (!autoTurnToAngle->IsScheduled()) && (autoPointTwo == false)) {

      simpleCrossAutoLine.reset(new SimpleCrossAutoLine);
      simpleCrossAutoLine->SetDistance(autoTwoNum);
      simpleCrossAutoLine->Schedule();
      autoPointTwo = true;

    } else if (autoTwoString == "Shoot") {

      autoShootCell.reset(new AutoShootCell);
      autoShootCell->Schedule();
      autoPointTwo = true;

    } else {
      autoStepTwo = true;
    }
}

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
