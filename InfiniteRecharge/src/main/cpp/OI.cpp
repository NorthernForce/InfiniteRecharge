#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/button/Trigger.h>
#include "OI.h"
#include "Constants.h"

#include "frc2/command/button/Button.h"
#include <frc2/command/button/JoystickButton.h>
#include "utilities/ComboControl.h"

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
#include "commands/Climb.h"
#include "commands/ShootByDist.h"
#include "commands/ManualWackyWheel.h"
#include "commands/StopIntake.h"

#include "commands/ResetCoordinates.h"
#include "commands/TuneRpmPid.h"
#include "commands/IndexPowerCells.h"
#include "commands/IntakeUp.h"
#include "commands/IntakeDown.h"

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI() {
    frc::SmartDashboard::PutNumber("Drive Speed:", 1.0);
    frc::SmartDashboard::PutNumber("Shooter Ramp Rate:", 0.2);
    InitControllers();
}

void OI::InitControllers() {
    driverController.reset(new frc::XboxController(Constants::driverController_id));
    manipulatorController.reset(new frc::XboxController(Constants::manipulatorController_id));
}

void OI::MapControllerButtons() {


  //Driver Controller
    // SimpleButton(driverController, Xbox::A_button).WhenPressed(new IntakePowerCell());
    frc2::Button([this] { return driverController->GetRawButton(Xbox::X_button); }).WhenPressed(new PushOutPowerCell());
    // frc2::Button([this] { return (driverController->GetRawAxis(XboxAxis::lt_trigger) > 0.5); }).WhileHeld(new ShootByDist());
    // frc2::Button([this] { return (driverController->GetRawAxis(XboxAxis::rt_trigger) > 0.5); }).WhenPressed(new PushOutPowerCell());
    frc2::Button([this] {return (driverController->GetRawAxis(XboxAxis::rt_trigger)); }).WhileHeld(new ShootCell());
    frc2::Button([this] {return (driverController->GetRawButton(Xbox::B_button)); }).WhileHeld(new PushOutPowerCell());
    frc2::Button([this] { return driverController->GetRawButton(Xbox::lt_bumper); }).WhenPressed(new ShiftGear(ShiftGear::Gear::Low));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::lt_bumper); }).WhenReleased(new ShiftGear(ShiftGear::Gear::High));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhileHeld(new IntakePowerCell());
    

   // frc2::Button([this] { return driverController->GetRawButton(Xbox::Y_button); }).WhenPressed(new IndexPowerCells());

    // frc2::Button([this] { return driverController->GetRawButton(Xbox::A_button); }).WhileHeld(new MoveToPowercell());

  //Manipulator Controller
    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::Y_button); }).WhenPressed(new AimShooterUp());
    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::B_button); }).WhenPressed(new AimShooterDown());
    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::menu_button); }).WhenPressed(new ResetCoordinates());
    frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::A_button); }).WhileHeld(new IntakeDown());
    //frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::X_button); }).WhileHeld(new IntakeUp());
    //frc2::Button([this] {return manipulatorController->GetRawButton(Xbox::X_button); }).WhileHeld(new ManualWackyWheel());



  //Testing Buttons
    //frc2::Button([this] { return driverController->GetRawButton(Xbox::X_button); }).WhileHeld(new TurnToAngle(180));
    //frc2::Button([this] { return driverController->GetRawButton(Xbox::menu_button); }).WhenPressed(new TuneRpmPid());
    //frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::A_button); }).WhenPressed(new PositionControl()); need color sensor that we asked for long ago
    //frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::X_button); }).WhenPressed(new RotationControl());
    // frc2::Button([this] { return manipulatorController->GetRawButton(Xbox::lt_bumper); }).WhileHeld(new ToggleArm()); Need to fix toggle arm at some point
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

frc2::Button OI::SimpleButton(std::shared_ptr<frc::GenericHID> controller, int btn) {
  return frc2::Button([this, controller, btn] { return controller->GetRawButton(btn); });
}

frc2::Button OI::SimpleAxis(std::shared_ptr<frc::GenericHID> controller, int axis, double threshold) {
  return frc2::Button([this, controller, axis, threshold] { return controller->GetRawAxis(axis) > threshold; });
} 