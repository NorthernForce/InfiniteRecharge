#include "OI.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/DriveWithJoystick.h"

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI() {}

void OI::InitControllers() {
    driverController.reset(new frc::XboxController(Constants::OI::driverController_id));
    manipulatorController.reset(new frc::XboxController(Constants::OI::manipulatorController_id));
}

void OI::MapControllerButtons() {
    
}

double OI::getDriveSpeedMultiplier() {
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed: ", 1.0);
    if (speedMultiplier < 0)
        speedMultiplier = 0;
    else if (speedMultiplier > 1)
        speedMultiplier = 1;

    return speedMultiplier;
}