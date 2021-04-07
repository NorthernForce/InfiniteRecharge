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
#include "commands/autonomous/AutoChallengeChooser.h"
#include "commands/autonomous/AutonomousBallSeek.h"
#include "commands/autonomous/AutoBallSeek.h"
#include "commands/autonomous/MoveToCoordinate.h"
#include "commands/autonomous/MoveThroughCoordinateSet.h"
#include "commands/TuneValue.h"
#include "commands/TestServo.h"

#include <cameraserver/CameraServer.h>
#include <frc2/command/ParallelCommandGroup.h>


void Robot::RobotInit() {
    container = std::make_shared<RobotContainer>();
    logger = std::make_unique<Logger>();

    /*
    frc::SmartDashboard::PutString("auto string input 1", "insert here");
    frc::SmartDashboard::PutString("auto 1 parameter", "");
    frc::SmartDashboard::PutString("auto string input 2", "insert here");
    frc::SmartDashboard::PutString("auto 2 parameter", "");
    frc::SmartDashboard::PutString("auto string input 3", "insert here");
    frc::SmartDashboard::PutString("auto 3 parameter", "");
    frc::SmartDashboard::PutString("auto string input 4", "insert here");
    frc::SmartDashboard::PutString("auto 4 parameter", "");
    frc::SmartDashboard::PutString("auto string input 5", "insert here");
    frc::SmartDashboard::PutString("auto 5 parameter", "");
    frc::SmartDashboard::PutNumberArray("Coordinate Set", 0);
    */


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

    frc::CameraServer::GetInstance()->StartAutomaticCapture();
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

void Robot::DisabledInit() {
//   RobotContainer::drivetrain->WriteLeftMotorPos("LeftTest");
//   RobotContainer::drivetrain->WriteRightMotorPos("RightTest");
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
    dashboardInput.push_back(frc::SmartDashboard::GetString("auto string input 1", "insert here"));
    dashboardInput.push_back(frc::SmartDashboard::GetString("auto string input 2", "insert here"));
    dashboardInput.push_back(frc::SmartDashboard::GetString("auto string input 3", "insert here"));
    dashboardInput.push_back(frc::SmartDashboard::GetString("auto string input 4", "insert here"));
    dashboardInput.push_back(frc::SmartDashboard::GetString("auto string input 5", "insert here"));

    dashboardParams.push_back(frc::SmartDashboard::GetString("auto 1 parameter", ""));
    dashboardParams.push_back(frc::SmartDashboard::GetString("auto 2 parameter", ""));
    dashboardParams.push_back(frc::SmartDashboard::GetString("auto 3 parameter", ""));
    dashboardParams.push_back(frc::SmartDashboard::GetString("auto 4 parameter", ""));
    dashboardParams.push_back(frc::SmartDashboard::GetString("auto 5 parameter", ""));

    RobotContainer::imu->ZeroRotation();

    //RobotContainer::drivetrain->PlayRecordedRun(RobotContainer::drivetrain->GetMotorVals("l"), RobotContainer::drivetrain->GetMotorVals("r"));

    //   frc2::SequentialCommandGroup{
    //   TurnToAngle(90),
    //   SimpleCrossAutoLine(),
    // }


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
      autoCommandScheduler.reset(new AutoCommandScheduler({       
        //Path A-Galactic
        //Red
        new IntakePowerCell(),
        new MoveToCoordinate(75, 30),
        new IntakePowerCell(),
        new MoveToCoordinate(135, 60),
        new IntakePowerCell(),
        new MoveToCoordinate(165, -30),
        new MoveToCoordinate(330, 0),
    }));
    //autoCommandScheduler.reset(new AutoCommandScheduler);
    //autoCommandScheduler->DashboardAuto({"Coordinate", "Turn"}, {"0, 36, 0.145", "30"});
}

void Robot::AutonomousPeriodic() {

  // auto command scheduler execution
  autoCommandScheduler->RunSequential();
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
void Robot::TeleopPeriodic() {
//   RobotContainer::drivetrain->RecordMotorPos();
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
