#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include "frc2/command/button/Button.h"
#include "OI.h"
#include "Constants.h"

#include "frc2/command/button/Button.h"
#include <frc2/command/button/JoystickButton.h>

#include "commands/SweepAICamera.h"
#include "commands/DriveWithJoystick.h"
#include "commands/ShiftGear.h"
#include "commands/SweepAICamera.h"
#include "commands/IntakePowerCell.h"
#include "commands/PushOutPowerCell.h"
#include "commands/ToggleArm.h"
#include "commands/ShootCell.h"

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
    double rtTriggerAxis = manipulatorController->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand);

    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhenPressed(new ShiftGear(ShiftGear::Gear::Low));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhenReleased(new ShiftGear(ShiftGear::Gear::High));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::A_button); }).WhileHeld(new SweepAICamera());

    frc2::Button([this] { return manipulatorController->GetRawButton(XboxAxis::lt_trigger); }).WhileHeld(new IntakePowerCell());
    frc2::Button([this] {return manipulatorController->GetRawButton(Xbox::lt_bumper); }).WhileHeld(new PushOutPowerCell());

    frc2::Button([this] {return manipulatorController->GetRawButton(Xbox::rt_bumper); }).WhenPressed(new ToggleArm());

    frc2::Button([this] {return manipulatorController->GetRawAxis(XboxAxis::rt_trigger); }).WhileHeld(new ShootCell(rtTriggerAxis));
}

double OI::getDriveSpeedMultiplier() {
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed:", 1.0);
    if (speedMultiplier < 0)
        speedMultiplier = 0;
    else if (speedMultiplier > 1)
        speedMultiplier = 1;
    return speedMultiplier;
}

double OI::getShootRampRateMultiplier() {
    double shootRampRateMultiplier = frc::SmartDashboard::GetNumber("Shooter Ramp Rate:", 0.2);
    if (shootRampRateMultiplier < 0)
        shootRampRateMultiplier = 0;
    else if (shootRampRateMultiplier > 1)
        shootRampRateMultiplier = 1;
    return shootRampRateMultiplier;
}
