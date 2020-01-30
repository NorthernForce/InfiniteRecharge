#pragma once

#include <frc/XboxController.h>

class OI {
 public:
  OI();
  void InitControllers();
  void MapControllerButtons();
  double getDriveSpeedMultiplier();

  static std::shared_ptr<frc::XboxController> driverController;
  static std::shared_ptr<frc::XboxController> manipulatorController;
};