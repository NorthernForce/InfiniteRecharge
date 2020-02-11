/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraMount.h"
#include "Constants.h"

CameraMount::CameraMount() 
{
    panServo.reset(new frc::Servo(Constants::Servo::panServo));
    tiltServo.reset(new frc::Servo(Constants::Servo::tiltServo));
    Init();
}

void CameraMount::Init()
{
    currentPan = 0;
    currentTilt = 0;
    previousPan = 0;
    previousTilt = 0;
    panDirection = 0;
    tiltDirection = 0;
}

void CameraMount::Pan(int degrees)
{
    previousPan = currentPan;
    currentPan = degrees;
    panServo->SetAngle(degrees);
}

int CameraMount::GetCurrentPan()
{
    currentPan = panServo->GetAngle();
    return currentPan;
}

int CameraMount::GetPreviousPan()
{
    return previousPan;
}

void CameraMount::Tilt(int degrees)
{
    previousTilt = currentTilt;
    currentTilt = degrees;
    tiltServo->SetAngle(degrees);
}

int CameraMount::GetCurrentTilt()
{
    currentTilt = tiltServo->GetAngle();
    return currentTilt;
}

int CameraMount::GetPreviousTilt()
{
    return previousTilt;
}

void CameraMount::SetToZero()
{
    Pan(0);
    Tilt(0);
}

void CameraMount::SetAngles(int panAngle, int tiltAngle)
{
    Pan(panAngle);
    Tilt(tiltAngle);
}

bool CameraMount::SweepForPowercells()
{
    Tilt(-15);

    for(int i=-91; i<=90; i++)
    {
        Pan(i);
        /* <-- Remove; AIVision
        if (RobotContainer::aiVisionTargetting->CheckForTarget()) 
        {
            servoAngleToTarget = i;
            return true;
        }
        */
    }
    for(int i=91; i>=-90; i--) 
    {
        Pan(i);
        /* <-- Remove; AiVision
        if (RobotContainer::aiVisionTargetting->CheckForTarget()) 
        {
            servoAngleToTarget = i;
            return true;
            
        }
        */
    }    
    return true;
}

int CameraMount::GetServoAngleToTarget()
{
    return servoAngleToTarget;
}


// This method will be called once per scheduler run
void CameraMount::Periodic() {}