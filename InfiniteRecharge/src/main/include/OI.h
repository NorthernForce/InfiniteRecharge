#pragma once

#include <frc/XboxController.h>

class OI {
 public:
  OI();
  void InitControllers();
  void MapControllerButtons();
  double getDriveSpeedMultiplier();
  enum class Xbox;
  enum class XboxAxis;
  enum class XboxPOV;

  static std::shared_ptr<frc::XboxController> driverController;
  static std::shared_ptr<frc::XboxController> manipulatorController;
};

enum class OI::Xbox { 
    A_button     = 1,
    B_button     = 2, 
    X_button     = 3, 
    Y_button     = 4, 
    rt_bumper    = 5, 
    lt_bumper    = 6, 
    menu_button  = 7, 
    view_button  = 8,
    lt_stick     = 9,
    rt_stick     = 10
};

enum class OI::XboxAxis {
    lt_X,
    lt_Y,
    lt_trigger,
    rt_trigger,
    rt_X,
    rt_Y
};

enum class OI::XboxPOV {
    up           = 0,
    up_right     = 45,
    right        = 90,
    down_right   = 135,
    down         = 180,
    down_left    = 225,
    left         = 270,
    left_up      = 315
};