/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TuneValue.h"
#include "frc/smartdashboard/SmartDashboard.h"

////TODO: Make valueToTune char

TuneValue::TuneValue(int valueToTune, std::unique_ptr<MoveToCoordinate> pidCommand, std::vector<double> pidValues, double increment, double accuracy) {
  tunedValue = valueToTune;
  commandToTune = std::move(pidCommand);
  values = pidValues;
  tuneIncremenet = increment;
  tuneAccuracy = accuracy;
}

// Called when the command is initially scheduled.
void TuneValue::Initialize() {
    commandFail = 0;
}

// Called repeatedly when this Command is scheduled to run
void TuneValue::Execute() {
  frc::SmartDashboard::PutBoolean("executing pid command", commandToTune->IsScheduled());
  if (!commandToTune->IsScheduled() && scheduleCommand) {
    commandToTune->Set(values);
    commandToTune->Schedule();
    scheduleCommand = false;
  }   
  else if (!commandToTune->IsScheduled() && !scheduleCommand) {
    scheduleCommand = true;
    if (!commandToTune->HasOscillated()) {
      values[tunedValue] -= tuneIncremenet;
      tuneIncremenet /= 4;
    }
    else {
      values[tunedValue] += tuneIncremenet; 
    }
  }
  else if (commandToTune->IsScheduled()) {
    frc::SmartDashboard::PutNumber("commandFail", commandFail);
    scheduleCommand = false;
    commandFail++;
    if (commandFail > 1000) {
      commandFail = 0;
      commandToTune->Cancel();
    }
  }
}

// Called once the command ends or is interrupted.
void TuneValue::End(bool interrupted) {}

// Returns true when the command should end.
bool TuneValue::IsFinished() { 
  return (tuneIncremenet < tuneAccuracy);
}