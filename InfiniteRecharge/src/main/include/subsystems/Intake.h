/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
#include <frc/DigitalInput.h>
#include "Constants.h"


class Intake : public frc2::SubsystemBase {
 public:
  enum class ArmState {
    armIsUp,
    armIsDown
  };

//"StorageState" = whether there is a PC (Ball) at a Conveyor Position
  enum class StorageState {
    PRESENT,                  //Have Ball
    EMPTY                    //No Ball
  };

  const int noEmptyPositionFound = -1;
  const int noFullPositionFound = -1;

  Intake();
  void InitMotorControllers();
  void InitBallPositionSensors();
  void SetInvertedFollower();
  void Periodic();
  void ResetZHBT();
  void TrevinRunConveyer(double speed = Constants::Intake::normal);
  bool TrevinIntakeDebug();
  bool TrevinIntakeCompact();


  void TakeInPowerCell();
  void SetIntakeSpeed(double speed);
  void PushOutPowerCell();
  int GetPowerCellCount();
  void Stop();
  void SetArmUp();
  void SetArmDown();
  void SetArm(double speed);
  double GetArmPosition();
  ArmState GetArmState();
  void RunConveyor();
  void RunConveyorToShoot();
  void StopConveyor();
  void ConveyorSetSpeed(double speed);
  double GetConveyerSpeed();
  bool IsConveyorEmpty();

  //Checks each Conveyor Storage Location and sets its "StorageState" in the array powerCellPosition
  void InventoryPowerCells(); ///set array and then set a counter

  //Returns the previously detemined "StorageState" of the specific Conveyor Storage Position (integer) given
  StorageState GetInventory(int position);

  int GetFirstEmptyPosition();
  int LowestFullPosition();
  
  
  double speed;

  ////TODO: add ramp rate?

 private:

  ArmState currentArmState;
  StorageState powerCellPosition[6];   //Holds the StorageState of the associated Conveyor Position
  const bool ballDetected = false;

  std::vector<frc::DigitalInput*> ballPosition;

  std::shared_ptr<WPI_TalonSRX> intakeTalon;
  std::shared_ptr<rev::CANSparkMax> armSpark;
  std::shared_ptr<rev::CANSparkMax> primaryConveyorSpark;
  std::shared_ptr<rev::CANSparkMax> followerConveyorSpark;

  bool zeroHasBeenTripped = false;
  bool fourHasBeenTripped = false;
  bool ballOccupancy[6];
  int powerCellCount = 0;
  double sparkSpeed;
};