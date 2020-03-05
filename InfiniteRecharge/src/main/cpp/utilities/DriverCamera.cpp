/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "utilities/DriverCamera.h"

DriverCamera::DriverCamera(std::string name, int width, int height, int fps) {

    frc::CameraServer::GetInstance()->StartAutomaticCapture(name, 1);
    camera = cs::UsbCamera(name, 0);
    camera.SetResolution(width, height);
    camera.SetFPS(fps);

    camServer.reset(new cs::MjpegServer(name, 1181));
    camServer->SetSource(camera);
}