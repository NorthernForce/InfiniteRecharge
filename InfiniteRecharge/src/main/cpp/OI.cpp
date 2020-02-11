#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include "frc2/command/button/Button.h"
#include "OI.h"
#include "Constants.h"

#include "commands/DriveWithJoystick.h"
#include "commands/ShiftGear.h"
#include "commands/SweepAICamera.h"

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI() {
    frc::SmartDashboard::PutNumber("Drive Speed:", 1.0);
    InitControllers();
}

void OI::InitControllers() {
    driverController.reset(new frc::XboxController(Constants::OI::driverController_id));
    manipulatorController.reset(new frc::XboxController(Constants::OI::manipulatorController_id));
}

void OI::MapControllerButtons() {
    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhenPressed(new ShiftGear(ShiftGear::Gear::Low));
    frc2::Button([this] { return driverController->GetRawButton(Xbox::rt_bumper); }).WhenReleased(new ShiftGear(ShiftGear::Gear::High));

    frc2::Button([this] { return driverController->GetRawButton(Xbox::A_button); }).WhileHeld(new SweepAICamera());
}

double OI::getDriveSpeedMultiplier() {
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed: ", 1.0);
    if (speedMultiplier < 0)
        speedMultiplier = 0;
    else if (speedMultiplier > 1)
        speedMultiplier = 1;
    return speedMultiplier;
}