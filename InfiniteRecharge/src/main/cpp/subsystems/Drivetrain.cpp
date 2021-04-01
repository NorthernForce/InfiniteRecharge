/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <RobotContainer.h>

Drivetrain::Drivetrain() {
    leftPrimarySpark = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveLeftPrimary, rev::CANSparkMax::MotorType::kBrushless);
    leftFollowerSpark1 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveLeftFollower1, rev::CANSparkMax::MotorType::kBrushless);
    leftFollowerSpark2 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveLeftFollower2, rev::CANSparkMax::MotorType::kBrushless);
    rightPrimarySpark = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveRightPrimary, rev::CANSparkMax::MotorType::kBrushless);
    rightFollowerSpark1 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveRightFollower1, rev::CANSparkMax::MotorType::kBrushless);
    rightFollowerSpark2 = std::make_shared<rev::CANSparkMax>(Constants::MotorIDs::driveRightFollower2, rev::CANSparkMax::MotorType::kBrushless);

////Execute Methods to set up Motor Controllers (Followers, Ramping Rates, and Inverted Motors)
    SetInvertedFollowers();
    ConfigureAllControllers();

    robotDrive = std::make_shared<frc::DifferentialDrive>(*leftPrimarySpark, *rightPrimarySpark);

    SetEncoderPosition(0);
}

void Drivetrain::SetInvertedFollowers() {
    leftFollowerSpark1->Follow(*leftPrimarySpark, true);
    leftFollowerSpark2->Follow(*leftPrimarySpark, true);
    rightFollowerSpark1->Follow(*rightPrimarySpark, true);
    rightFollowerSpark2->Follow(*rightPrimarySpark, true);
}

void Drivetrain::ConfigureAllControllers() {
    ConfigureController(*leftPrimarySpark);
    ConfigureController(*leftFollowerSpark1);
    ConfigureController(*leftFollowerSpark2);
    ConfigureController(*rightPrimarySpark);
    ConfigureController(*rightFollowerSpark1);
    ConfigureController(*rightFollowerSpark2);

////Configure SPARK PID Controllers
    leftPID  = std::make_shared<rev::CANPIDController>(leftPrimarySpark->GetPIDController());
    rightPID = std::make_shared<rev::CANPIDController>(rightPrimarySpark->GetPIDController());

    this->setPID();

}

////JJC: Sets the SPARK Inernal PID Controller Parameters
void Drivetrain::setPID()
{

 //// read PID coefficients from SmartDashboard
    double p = frc::SmartDashboard::GetNumber("P Gain", 0);
    double i = frc::SmartDashboard::GetNumber("I Gain", 0);
    double d = frc::SmartDashboard::GetNumber("D Gain", 0);
    double iz = frc::SmartDashboard::GetNumber("I Zone", 0);
    double ff = frc::SmartDashboard::GetNumber("Feed Forward", 0);
    double max = frc::SmartDashboard::GetNumber("Max Output", 0);
    double min = frc::SmartDashboard::GetNumber("Min Output", 0);

    // if PID coefficients on SmartDashboard have changed, write new values to controller
    if((p != kP)) { leftPID->SetP(p); rightPID->SetP(p); kP = p; }
    if((i != kI)) { leftPID->SetI(i); rightPID->SetI(i); kI = i; }
    if((d != kD)) { leftPID->SetD(d); rightPID->SetD(d); kD = d; }
    if((iz != kIz)) { leftPID->SetIZone(iz); rightPID->SetIZone(iz); kIz = iz; }
    if((ff != kFF)) { leftPID->SetFF(ff); rightPID->SetFF(ff); kFF = ff; }
    if((max != kMaxOutput) || (min != kMinOutput)) 
    { 
      leftPID->SetOutputRange(min, max); 
      rightPID->SetOutputRange(min, max); 
      kMinOutput = min;
      kMaxOutput = max; 
    }

    frc::SmartDashboard::PutNumber("P Gain", kP);
    frc::SmartDashboard::PutNumber("I Gain", kI);
    frc::SmartDashboard::PutNumber("D Gain", kD);
    frc::SmartDashboard::PutNumber("I Zone", kIz);
    frc::SmartDashboard::PutNumber("Feed Forward", kFF);
    frc::SmartDashboard::PutNumber("Min Output", kMinOutput);
    frc::SmartDashboard::PutNumber("Max Output", kMaxOutput);

}

void Drivetrain::Drive(double speed, double rotation) {
    robotDrive->ArcadeDrive(speed, rotation * 0.85);
}

void Drivetrain::DriveUsingSpeeds(double leftSpeed, double rightSpeed) {
    this->setPID();
    leftPID->SetReference(-leftSpeed, rev::ControlType::kVelocity);
    leftPrimarySpark->Set(-leftSpeed);
    rightPID->SetReference(rightSpeed, rev::ControlType::kVelocity);
    rightPrimarySpark->Set(rightSpeed);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    frc::SmartDashboard::PutNumber("currenEncoderReal", GetEncoderRotations().first);
}

// Sets each Spark motor controller with current limits, a speed ramp, and brake
void Drivetrain::ConfigureController(rev::CANSparkMax& controller) {
  controller.SetSecondaryCurrentLimit(secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(currentLimit);
  if(!controller.IsFollower())
  {
    controller.SetClosedLoopRampRate(rampRate);
    controller.SetOpenLoopRampRate(rampRate);
  }
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

double Drivetrain::GetLeftRPM() {
    return leftPrimarySpark->GetEncoder().GetVelocity() * -1;
}

double Drivetrain::GetRightRPM() {
    return rightPrimarySpark->GetEncoder().GetVelocity() * -1;
}

double Drivetrain::GetAvgRPM() {
    return ((GetLeftRPM() + GetRightRPM()) / 2);
}

std::pair<double, double> Drivetrain::GetEncoderRotations() {
    double leftSideRotations = leftPrimarySpark->GetEncoder().GetPosition();
    double rightSideRotations = rightPrimarySpark->GetEncoder().GetPosition() * -1;
    return std::make_pair(leftSideRotations, rightSideRotations);
}

double Drivetrain::GetAvgEncoderRotations() {
    double left = GetEncoderRotations().first;
    double right = GetEncoderRotations().second;
    double avgRots = (left + right) / 2;
    return avgRots;
}

// This does not work as intended, use autodrive command instead
void Drivetrain::SimpleDriveWithEncoder(double desiredEncoder) {
    if ((leftPrimarySpark->GetEncoder().GetPosition() && rightPrimarySpark->GetEncoder().GetPosition()) <= desiredEncoder) {
        leftPrimarySpark->Set(0.3);
        rightPrimarySpark->Set(0.3);
    }
}

void Drivetrain::SetEncoderPosition(double position) {
    leftPrimarySpark->GetEncoder().SetPosition(position);
    rightPrimarySpark->GetEncoder().SetPosition(position);
}

int Drivetrain::GetSpeedInInchesPerSecond() {
    prevEncoder = currentEncoder;
    currentEncoder = GetAvgEncoderRotations();
    double changeInPosition = abs(currentEncoder - prevEncoder);

    int convertToInchesMultiplier;
    if (RobotContainer::driveShifter->GetGear() == DriveShifter::Gear::Low)
        convertToInchesMultiplier = Constants::Shifting::lowMultiplier; 
    else
        convertToInchesMultiplier = Constants::Shifting::highMultiplier;
        
    return convertToInchesMultiplier * changeInPosition * loopCyclesInOneSecond;
}

void Drivetrain::RecordMotorPos(){
    leftMotorPos.push_back(leftPrimarySpark->GetEncoder().GetPosition());
    rightMotorPos.push_back(rightPrimarySpark->GetEncoder().GetPosition());
}

void Drivetrain::WriteLeftMotorPos(std::string fileName) {
    RobotContainer::interactTextFiles->WriteTextFile(leftMotorPos, fileName);
}

void Drivetrain::WriteRightMotorPos(std::string fileName) {
    RobotContainer::interactTextFiles->WriteTextFile(rightMotorPos, fileName);
}

void Drivetrain::PlayRecordedRun(std::vector<double> leftMotorVals, std::vector<double> rightMotorVals) {
    
    static int i = 0;

    for(; i < leftMotorVals.size(); i++) {
        while(leftMotorVals[i] > leftPrimarySpark->GetEncoder().GetPosition()) {
            leftPrimarySpark->Set(.13);
        }
        while(rightMotorVals[i] > rightPrimarySpark->GetEncoder().GetPosition()) {
            rightPrimarySpark->Set(.13);
        }

        if((rightMotorVals[i] <= rightPrimarySpark->GetEncoder().GetPosition()) && (leftMotorVals[i] <= leftPrimarySpark->GetEncoder().GetPosition())) {
            leftPrimarySpark->Set(0);
            rightPrimarySpark->Set(0);
        }
    }
}