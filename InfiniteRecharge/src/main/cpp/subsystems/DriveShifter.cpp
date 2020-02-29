/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveShifter.h"
#include "Constants.h"
#include "RobotContainer.h"
#include "subsystems/Drivetrain.h"

std::shared_ptr<rev::CANSparkMax> Drivetrain::leftPrimarySpark;
std::shared_ptr<rev::CANSparkMax> Drivetrain::rightPrimarySpark;
std::shared_ptr<frc::DifferentialDrive> Drivetrain::robotDrive;

using Gear = DriveShifter::Gear;

DriveShifter::DriveShifter() : 
  leftSideSpark(Drivetrain::leftPrimarySpark),
  rightSideSpark(Drivetrain::rightPrimarySpark)
{
    shifter.reset(new frc::Solenoid(Constants::PCMCanBusID, 1));
    BeginShift(false);
}

// This method will be called once per scheduler run
void DriveShifter::Periodic() {
    if (shiftCountdown > 0)
        shiftCountdown -= 1;
}

void DriveShifter::Shift(Gear gear) {
    if(gear != currentGear)
	{
		currentGear = gear;
		if(currentGear == Gear::High)
		{
			BeginShift(false);
			leftSideSpark->Set(0);
			rightSideSpark->Set(0);
		}
		else
		{
			BeginShift(true);
            const auto leftSpeedInRPM = RobotContainer::drivetrain->GetLeftRPM();
			const auto rightSpeedInRPM = RobotContainer::drivetrain->GetRightRPM();
			CheckVelocityForShift(rightSpeedInRPM, leftSpeedInRPM);
		}
		Drivetrain::robotDrive->SetSafetyEnabled(false);
	}
}

void DriveShifter::CheckVelocityForShift(int leftSpeedInRPM, int rightSpeedInRPM) {
	int averageSpeedInRPM = (abs(leftSpeedInRPM) + abs(rightSpeedInRPM)) / 2;
	if(averageSpeedInRPM > velocityForShift) {
		leftSideSpark->Set(leftSpeedInRPM > 0 ? 1 : -1);
		rightSideSpark->Set(rightSpeedInRPM > 0 ? 1 : -1);
	}
}

Gear DriveShifter::GetGear() {
    return currentGear;
}

void DriveShifter::BeginShift(bool shift) {
    shifter->Set(shift);
    shiftCountdown = 5;
}

bool DriveShifter::IsShiftDone() const {
    return shiftCountdown <=0;
}