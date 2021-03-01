/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/PCM.h"
#include "Constants.h"

PCM::PCM() {
    compressor.reset(new frc::Compressor(Constants::PCMCanBusID));
    compressor->SetClosedLoopControl(true);
}

// This method will be called once per scheduler run
void PCM::Periodic() {}