#pragma once

#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/button/POVButton.h>

#include "commands/TurnToAngle.h"
#include "commands/autonomous/SimpleCrossAutoLine.h"

class OI {
 public:
    OI();
    void InitControllers();
    void MapControllerButtons();
    void MapControllerButtonsNew();
    //frc::SendableChooser<frc2::Command*> DisplayAutonomousChooser();
    std::pair<double, double> GetDriveControls();
    void SetControllerRumble(frc::XboxController *controller, double value=0, bool lightly=false);

    static std::shared_ptr<frc::XboxController> driverController;
    static std::shared_ptr<frc::XboxController> manipulatorController;

    enum Xbox { 
        A_button     = 1,
        B_button     = 2, 
        X_button     = 3, 
        Y_button     = 4, 
        lt_bumper    = 5,
        rt_bumper    = 6,  
        menu_button  = 7, 
        view_button  = 8,
        lt_stick     = 9,
        rt_stick     = 10
    };

    enum XboxAxis {
        lt_X,
        lt_Y,
        lt_trigger,
        rt_trigger,
        rt_X,
        rt_Y
    };

    enum XboxPOV {
        up           = 0,
        up_right     = 45,
        right        = 90,
        down_right   = 135,
        down         = 180,
        down_left    = 225,
        left         = 270,
        left_up      = 315
    };
    const static auto leftHand = frc::XboxController::JoystickHand::kLeftHand;
    const static auto rightHand = frc::XboxController::JoystickHand::kRightHand;

 private:
    void UpdateDriveSpeedMultiplier();
    double CheckAndLimitValue(double value, double upperLimit=1, double lowerLimit=0);
    double speed;
    double rotation;
    double driveSpeedMultiplier;
    frc2::Button SimpleButton(std::shared_ptr<frc::GenericHID> controller, uint8_t btn);
    frc2::Button SimpleAxis(std::shared_ptr<frc::GenericHID> controller, uint8_t axis, double threshold=0.5);
    frc2::POVButton SimplePOV(std::shared_ptr<frc::GenericHID> controller, uint16_t degrees);
    uint8_t cyclesSinceDriveSpeedCheck;
};