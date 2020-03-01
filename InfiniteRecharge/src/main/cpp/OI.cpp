#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include "frc2/command/button/Button.h"
#include "OI.h"
#include "Constants.h"

#include "frc2/command/button/Button.h"
#include <frc2/command/button/JoystickButton.h>
#include "utilities/ComboControl.h"
#include "utilities/SimpleAxis.h"

#include "commands/SweepAICamera.h"
#include "commands/DriveWithJoystick.h"
#include "commands/ShiftGear.h"
#include "commands/SweepAICamera.h"
#include "commands/IntakePowerCell.h"
#include "commands/PushOutPowerCell.h"
#include "commands/ToggleArm.h"
#include "commands/ShootCell.h"
#include "commands/PositionControl.h"
#include "commands/RotationControl.h"
#include "commands/TurnToAngle.h"
#include "commands/autonomous/InFrontOfFoesTrench.h"
#include "commands/autonomous/InFrontOfGoal.h"
#include "commands/autonomous/InFrontOfOurTrench.h"
#include "commands/autonomous/CrossAutoLine.h"
#include "commands/autonomous/DoNothing.h"
#include "commands/AimShooterUp.h"
#include "commands/AimShooterDown.h"
#include "commands/MoveToLimelight.h"
#include "commands/RunIntakeMotor.h"

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI() {
    frc::SmartDashboard::PutNumber("Drive Speed:", 1.0);
    frc::SmartDashboard::PutNumber("Shooter Ramp Rate:", 0.2);
    InitControllers();
}

void OI::DisplayAutonomousChooser() {
  autonomousChooser.SetDefaultOption("1) Cross auto line", new CrossAutoLine());
  autonomousChooser.AddOption("2) In front of goal", new InFrontOfGoal());
  autonomousChooser.AddOption("3) In front of our trench", new InFrontOfOurTrench());
  autonomousChooser.AddOption("4) In front of foe's trench", new InFrontOfFoesTrench());
  autonomousChooser.AddOption("4) Do Nothing", new DoNothing());

  frc::SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);
}

void OI::InitControllers() {
    driverController.reset(new frc::XboxController(Constants::driverController_id));
    manipulatorController.reset(new frc::XboxController(Constants::manipulatorController_id));
}

void OI::MapControllerButtons() {
    double rtTriggerAxis = manipulatorController->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand);
    auto ltTriggerAxis = new SimpleAxis(manipulatorController, XboxAxis::lt_trigger);

    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhenPressed(new ShiftGear(ShiftGear::Gear::Low));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhenReleased(new ShiftGear(ShiftGear::Gear::High));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::A_button); }).WhileHeld(new SweepAICamera());
    frc2::Button([this] { return driverController->GetRawButton(Xbox::lt_bumper); }).WhileHeld(new TurnToAngle(180));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::A_button); }).WhileHeld(new MoveToLimelight());

    frc2::Button([this, ltTriggerAxis] { return ltTriggerAxis->Get(); }).WhileHeld(new IntakePowerCell());
    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::lt_bumper); }).WhileHeld(new PushOutPowerCell());

    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::rt_bumper); }).WhenPressed(new ToggleArm());

    frc2::Button([this] { return manipulatorController->GetRawAxis(XboxAxis::rt_trigger); }).WhileHeld(new ShootCell(rtTriggerAxis));
    frc2::Button([this] { return manipulatorController->GetRawButton(XboxPOV::up); }).WhenPressed(new AimShooterUp);
    frc2::Button([this] { return manipulatorController->GetRawButton(XboxPOV::down); }).WhenPressed(new AimShooterDown);

    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::X_button); }).WhenPressed(new PositionControl());
    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::B_button); }).WhenPressed(new RotationControl());
}

std::pair<double, double> OI::GetDriveControls() {
  double speed = driverController->GetY(frc::XboxController::JoystickHand::kLeftHand);
  double rotation = driverController->GetX(frc::XboxController::JoystickHand::kRightHand) *-1;
  double multiplier = GetDriveSpeedMultiplier();
  return std::make_pair(speed*multiplier, rotation*multiplier);
}

double OI::GetShooterRampRate() {
    double shootRampRateMultiplier = frc::SmartDashboard::GetNumber("Shooter Ramp Rate:", 0.2);
    return CheckAndLimitValue(shootRampRateMultiplier);
}

double OI::GetDriveSpeedMultiplier() {
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed:", 1.0);
    return CheckAndLimitValue(speedMultiplier);
}

void OI::SetControllerRumble(frc::XboxController *controller, double value, bool lightly) {
  if (lightly)
    controller->SetRumble(frc::GenericHID::RumbleType::kRightRumble, value);
  else
    controller->SetRumble(frc::GenericHID::RumbleType::kLeftRumble, value);
}

double OI::CheckAndLimitValue(double value, double upperLimit, double lowerLimit) {
  if (value < lowerLimit)
    value = lowerLimit;
  else if (value > upperLimit)
    value = upperLimit;
  return value;
}