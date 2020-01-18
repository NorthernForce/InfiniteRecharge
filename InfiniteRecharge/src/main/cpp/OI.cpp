#include "OI.h"
#include "Constants.h"
#include "frc/smartdashboard/SmartDashboard.h"

OI::OI() {
    driverController.reset(new frc::XboxController(Constants::OI::driverController_id));
    manipulatorController.reset(new frc::XboxController(Constants::OI::manipulatorController_id));
}

std::pair<double, double> OI::getSteeringControls() {

    double speed = driverController->GetY(frc::XboxController::kLeftHand);
    double rotation = driverController->GetX(frc::XboxController::kRightHand);
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed: ", 1.0);

    if (speedMultiplier < 0)
        speedMultiplier = 0;
    else if (speedMultiplier > 1)
        speedMultiplier = 1;

    return std::make_pair(speed, rotation);

}