/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TuneValue.h"

////TODO: Make valueToTune char

TuneValue::TuneValue(int valueToTune, std::unique_ptr<frc2::Command> pidCommand, std::vector<double> pidValues, double increment, double accuracy) {
  tunedValue = valueToTune;
  commandToTune = std::move(pidCommand);
  values = pidValues;
  tuneIncremenet = increment;
  tuneAccuracy = accuracy;

}

// Called when the command is initially scheduled.
void TuneValue::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TuneValue::Execute() {
  if (!commandToTune->IsScheduled() && scheduleCommand) {
    commandToTune->Set(values);
    commandToTune->Schedule();
    scheduleCommand = false;
  }   
  if (!commandToTune->IsScheduled() && !scheduleCommand) {
    scheduleCommand = true;
    if (!commandToTune->HasOscillated()) {
      values[tunedValue] -= tuneIncremenet;
      tuneIncremenet /= 3;
    }
    else {
      values[tunedValue] += tuneIncremenet;
    }
  }

// Called once the command ends or is interrupted.
void TuneValue::End(bool interrupted) {}

// Returns true when the command should end.
bool TuneValue::IsFinished() { 
  return (tuneIncremenet < tuneAccuracy);
}