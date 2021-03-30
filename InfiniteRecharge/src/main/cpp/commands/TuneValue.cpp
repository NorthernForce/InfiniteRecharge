/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TuneValue.h"
#include "frc/smartdashboard/SmartDashboard.h"

////TODO: Make valueToTune char

TuneValue::TuneValue(int valueToTune, std::vector<double> parameters, std::vector<double> pidValues, double increment, double accuracy) {
  tunedValue = valueToTune;
  commandToTune = std::make_unique<MoveToCoordinate>(CPlane::Point(parameters[0], parameters[1]), parameters[2]);
  values = pidValues;
  tuneIncremenet = increment;
  tuneAccuracy = accuracy;
  commandToTuneParams = parameters;
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
    if (commandFail > 200) {
      commandFail = 0;
      commandToTune->Cancel();
      commandToTune.reset(new MoveToCoordinate(CPlane::Point(commandToTuneParams[0], commandToTuneParams[1]), commandToTuneParams[2]));
    }
  }
}

// Called once the command ends or is interrupted.
void TuneValue::End(bool interrupted) {}

// Returns true when the command should end.
bool TuneValue::IsFinished() { 
  return (tuneIncremenet < tuneAccuracy);
}