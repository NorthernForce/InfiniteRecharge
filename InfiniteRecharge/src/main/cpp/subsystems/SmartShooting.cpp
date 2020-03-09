/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SmartShooting.h"
#include "RobotContainer.h"

SmartShooting::SmartShooting() {}

// This method will be called once per scheduler run
void SmartShooting::Periodic() {}

bool SmartShooting::ShooterIsOn() {
    return RobotContainer::oi->driverController->GetRawAxis(OI::XboxAxis::rt_trigger) > 0.5;
}

double SmartShooting::GetDistance() {
    return RobotContainer::ultrasonic->GetDistance();
}

void SmartShooting::ControlDistance() {
    const double cutOffLow = 75;
    const double cutOffHigh = 75;

    if (RobotContainer::shooter->GetState() && ShooterIsOn() && (GetDistance() < cutOffHigh)) {
        // Move Back
    }
    else if (!RobotContainer::shooter->GetState() && ShooterIsOn() && (GetDistance() > cutOffLow)) {
        // Move Foward
    }
}

double SmartShooting::WantedShooterRPM() {
    double d = GetDistance();
    double dSquared = d * d;
    double dCubed = dSquared * d;
    double dQuad = dCubed * d;
    double wantedRPM = (0)*d + (0)/d + (0)*dSquared + (0)/dSquared + (0)*dCubed + (0)/dCubed + (0)*dQuad + (0)/dQuad;
    return wantedRPM;
}

void SmartShooting::ControlShooterRPM() {

}