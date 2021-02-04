#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include "OI.h"
#include "Constants.h"

#include "utilities/ComboControl.h"

#include "commands/DriveWithJoystick.h"
#include "commands/ShiftGear.h"
#include "commands/TurnToTarget.h"
#include "commands/IntakePowerCell.h"
#include "commands/PushOutPowerCell.h"
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
#include "commands/ReverseConveyor.h"
#include "commands/ResetCoordinates.h"
#include "commands/IndexPowerCells.h"
#include "commands/DecreaseShooterRPM.h"
#include "commands/IncreaseShooterRPM.h"
#include "commands/ManualIntake.h"
#include "commands/ManualShooter.h"
#include "commands/ManualConveyor.h"
#include "commands/ManualIntakeBackward.h"
#include "commands/TrevinIntake.h"
#include "commands/ZeroRobotAngle.h"
#include "commands/ZeroRobotPosition.h"

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI() {
    frc::SmartDashboard::PutNumber("Drive Speed:", 1.0);
    frc::SmartDashboard::PutNumber("Shooter Ramp Rate:", 0.2);
    frc::SmartDashboard::PutNumber("Shooter RPM: ", 0.5);    
    InitControllers();
}

void OI::InitControllers() {
    driverController = std::make_shared<frc::XboxController>(Constants::driverController_id);
    manipulatorController = std::make_shared<frc::XboxController>(Constants::manipulatorController_id);
}

void OI::MapControllerButtons() {
    SimpleAxis(driverController, XboxAxis::rt_trigger).WhileHeld(new ShootCell);
    SimpleButton(driverController, Xbox::B_button).WhileHeld(new PushOutPowerCell);
    SimpleButton(driverController, Xbox::lt_bumper).WhenPressed(new ShiftGear(ShiftGear::Gear::Low));
    SimpleButton(driverController, Xbox::lt_bumper).WhenReleased(new ShiftGear(ShiftGear::Gear::High));
    SimpleButton(driverController, Xbox::rt_bumper).WhileHeld(new IntakePowerCell);
    SimpleButton(driverController, Xbox::X_button).WhileHeld(new ReverseConveyor);
    SimpleButton(driverController, Xbox::A_button).WhileHeld(new MoveToLimelight);
    SimpleButton(driverController, Xbox::Y_button).WhileHeld(new TrevinIntake);
    SimpleButton(driverController, Xbox::menu_button).WhileHeld(new ZeroRobotAngle);
    SimpleButton(driverController, Xbox::view_button).WhileHeld(new ZeroRobotPosition);
    
    //a and x no longer in use
    SimpleButton(manipulatorController, Xbox::Y_button).WhenPressed(new AimShooterUp);
    SimpleButton(manipulatorController, Xbox::B_button).WhenPressed(new AimShooterDown());
    SimpleButton(manipulatorController, Xbox::rt_bumper).WhileHeld(new ManualShooter);
    SimpleAxis(manipulatorController, XboxAxis::rt_trigger).WhileHeld(new ManualIntake);
    SimpleAxis(manipulatorController, XboxAxis::lt_trigger).WhileHeld(new ManualIntakeBackward);
    SimpleButton(manipulatorController, Xbox::lt_bumper).WhileHeld(new ManualConveyor);
    SimpleButton(manipulatorController, XboxPOV::up).WhenPressed(new IncreaseShooterRPM);
    SimpleButton(manipulatorController, XboxPOV::down).WhenPressed(new DecreaseShooterRPM);
}

std::pair<double, double> OI::GetDriveControls() {
  double speed = driverController->GetY(frc::XboxController::JoystickHand::kLeftHand);
  double rotation = driverController->GetX(frc::XboxController::JoystickHand::kRightHand) *-1;
  double multiplier = GetDriveSpeedMultiplier();
  return std::make_pair(speed*multiplier, rotation*multiplier);
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

frc2::Button OI::SimplePOV(std::shared_ptr<frc::GenericHID> controller, int degs) {
    return frc2::Button([this, controller, degs] { return (controller->GetPOV(degs) == degs); });
}