#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include "OI.h"
#include "Constants.h"

#include "triggers/ComboControl.h"
#include "triggers/RawAxis.h"
#include "triggers/RawButton.h"

#include "commands/DriveWithJoystick.h"
#include "commands/ShiftGear.h"

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

namespace {
    void WhenPressed(frc2::Trigger* trigger, frc2::Command* command) {
        trigger->WhenActive(command);
    }

    void WhenReleased(frc2::Trigger* trigger, frc2::Command* command) {
        trigger->WhenInactive(command);
    }

    void WhileHeld(frc2::Trigger* trigger, frc2::Command* command) {
        trigger->WhileActiveContinous(command);
    }
}

OI::OI() {}

void OI::InitControllers() {
    driverController.reset(new frc::XboxController(Constants::OI::driverController_id));
    manipulatorController.reset(new frc::XboxController(Constants::OI::manipulatorController_id));
}

void OI::MapControllerButtons() {
    WhenPressed(new RawButton<OI::Xbox>(driverController, Xbox::rt_bumper), new ShiftGear(ShiftGear::Gear::High));
    WhenReleased(new RawButton<OI::Xbox>(driverController, Xbox::rt_bumper), new ShiftGear(ShiftGear::Gear::Low));
}

double OI::getDriveSpeedMultiplier() {
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed: ", 1.0);
    if (speedMultiplier < 0)
        speedMultiplier = 0;
    else if (speedMultiplier > 1)
        speedMultiplier = 1;

    return speedMultiplier;
}