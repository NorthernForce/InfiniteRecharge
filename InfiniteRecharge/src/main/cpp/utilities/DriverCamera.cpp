// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #include "utilities/DriverCamera.h"
// #include <cameraserver/CameraServer.h>

// DriverCamera::DriverCamera(std::string name, std::string devPath, int width, int height, int fps, bool flipOutput) {
//     m_name = name;
//     m_devPath = devPath;
//     m_flipOutput = flipOutput;

//     camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture(m_name, m_devPath));
//     camera->SetResolution(width, height);
//     camera->SetFPS(fps);
// }

// const std::string DriverCamera::defaultSettings = 
//   "brightness=133,"
//   "contrast=5,"
//   "saturation=83,"
//   "white_balance_temperature_auto=1,"
//   "power_line_frequency=2,"
//   "sharpness=25,"
//   "backlight_compensation=0,"
//   "exposure_auto=1,"
//   "exposure_absolute=156";

