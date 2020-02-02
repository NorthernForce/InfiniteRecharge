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
    shifter.reset(new frc::DoubleSolenoid(Constants::PCM::shifterDS_id.first,Constants::PCM::shifterDS_id.second));
    BeginShift(frc::DoubleSolenoid::Value::kForward);
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
			BeginShift(frc::DoubleSolenoid::Value::kReverse);
			leftSideSpark->Set(0);
			rightSideSpark->Set(0);
		}
		else
		{
			BeginShift(frc::DoubleSolenoid::Value::kForward);
            const auto leftSpeedInRPM = leftSideSpark->GetEncoder().GetVelocity();
			const auto rightSpeedInRPM = rightSideSpark->GetEncoder().GetVelocity();
			if(abs(leftSpeedInRPM) + abs(rightSpeedInRPM) > 100)
			{
				leftSideSpark->Set(leftSpeedInRPM > 0 ? 1 : -1);
				rightSideSpark->Set(rightSpeedInRPM > 0 ? 1 : -1);
			}
		}
		Drivetrain::robotDrive->SetSafetyEnabled(false);
	}
}

Gear DriveShifter::GetGear() {
    return currentGear;
}

void DriveShifter::BeginShift(const frc::DoubleSolenoid::Value value) {
    shifter->Set(value);
    shiftCountdown = 5;
}

bool DriveShifter::IsShiftDone() const {
    return shiftCountdown <=0;
}