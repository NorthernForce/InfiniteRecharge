/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <string>
#include <cameraserver/CameraServer.h>
#include "cscore_oo.h"

class DriverCamera {
 public:
  DriverCamera(std::string name, std::string devPath, int width, int height, int fps);

 private:
  cs::UsbCamera camera;
  std::shared_ptr<cs::MjpegServer> camServer;
  const int settingsChangeDelayMillis = 250;
};
