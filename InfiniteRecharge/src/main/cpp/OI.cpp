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
#include "commands/ToggleArm.h"
#include "commands/ShootCell.h"
#include "commands/RotationControl.h"
#include "commands/TurnToAngle.h"
#include "commands/AimShooterUp.h"
#include "commands/AimShooterDown.h"
#include "commands/MoveToLimelight.h"
#include "commands/ShootByDist.h"
#include "commands/StopIntake.h"
#include "commands/ResetCoordinates.h"
#include "commands/IntakeUp.h"
#include "commands/IntakeDown.h"
#include "commands/DecreaseShooterRPM.h"
#include "commands/IncreaseShooterRPM.h"
#include "commands/ManualIntake.h"
#include "commands/ManualShooter.h"
#include "commands/ManualConveyor.h"
#include "commands/TrevinIntake.h"
#include "commands/ZeroRobotAngle.h"
#include "commands/ZeroRobotPosition.h"
#include "commands/LazySusanLeft.h"
#include "commands/LazySusanRight.h"
#include "commands/HoodUp.h"
#include "commands/HoodDown.h"
#include "commands/ToggleLimelight.h"

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
    SimpleButton(driverController, Xbox::A_button).WhileHeld(new MoveToLimelight);
    SimpleButton(driverController, Xbox::Y_button).WhenPressed(new ToggleLimelight);
    SimpleButton(driverController, Xbox::menu_button).WhileHeld(new ZeroRobotAngle);
    SimpleButton(driverController, Xbox::view_button).WhileHeld(new ZeroRobotPosition);
    
    SimpleButton(manipulatorController, Xbox::X_button).WhileHeld(new LazySusanLeft);
    SimpleButton(manipulatorController, Xbox::B_button).WhileHeld(new LazySusanRight);
    SimpleButton(manipulatorController, Xbox::A_button).WhileHeld(new IntakeDown);
    SimpleButton(manipulatorController, Xbox::Y_button).WhileHeld(new IntakeUp);
    SimpleButton(manipulatorController, Xbox::rt_bumper).WhileHeld(new ManualIntake);
    SimpleAxis(manipulatorController, XboxAxis::rt_trigger).WhileHeld(new ManualShooter);
    SimpleButton(manipulatorController, Xbox::lt_bumper).WhileHeld(new ManualConveyor);
    SimpleAxis(manipulatorController, XboxAxis::lt_Y, 0.5).WhileHeld(new HoodUp);
    SimpleAxis(manipulatorController, XboxAxis::lt_Y, -0.5).WhileHeld(new HoodDown);

}

std::pair<double, double> OI::GetDriveControls() {
    speed = driverController->GetY(frc::XboxController::JoystickHand::kLeftHand);
    rotation = driverController->GetX(frc::XboxController::JoystickHand::kRightHand) *-1;
    UpdateDriveSpeedMultiplier();
    return std::make_pair(speed*driveSpeedMultiplier, rotation*driveSpeedMultiplier);
}

void OI::UpdateDriveSpeedMultiplier() {
    driveSpeedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed:", 1.0);
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

frc2::Button OI::SimpleButton(std::shared_ptr<frc::GenericHID> controller, uint8_t btn) {
  return frc2::Button([this, controller, btn] { return controller->GetRawButton(btn); });
}

frc2::Button OI::SimpleAxis(std::shared_ptr<frc::GenericHID> controller, uint8_t axis, double threshold) {
    return frc2::Button([this, controller, axis, threshold] {
        if (threshold < 0)
            return controller->GetRawAxis(axis) < threshold;
        else
            return controller->GetRawAxis(axis) > threshold;
    });
}

frc2::POVButton OI::SimplePOV(std::shared_ptr<frc::GenericHID> controller, uint16_t degs) {
    return frc2::POVButton(controller.get(), degs);
}