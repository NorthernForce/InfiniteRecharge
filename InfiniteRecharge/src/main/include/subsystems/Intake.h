/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
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
    EMPTY                     //No Ball
  };

//Digital Ports Assigned to each Position
  const int position0 = 0;
  const int position1 = 1;
  const int position2 = 2;
  const int position3 = 3;
  const int position4 = 4;
  const int position5 = 5;

  const int noEmptyPositionFound = -1;

  Intake();
  void Periodic();
  void SetFollowers();
  void TakeInPowercell();
  void PushOutPowercell();
  void Stop();
  void SetArmUp();
  void SetArmDown();
  ArmState GetArmState();
  void RunConveyor();
  void StopConveyor();

  //Checks each Conveyor Storage Location and sets its "StorageState" in the array powerCellPosition
  void InventoryPowerCells(); ///set array and then set a counter

  //Returns the previously detemined "StorageState" of the specific Conveyor Storage Position (integer) given
  StorageState GetInventory(int position);

  //Return the First Position in the Conveyor Storage that is empty (no PC).
  int GetFirstEmptyPosition();

  ////TODO: add ramp rate?

 private:
  ArmState currentArmState;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  StorageState powerCellPosition[6];   //Holds the StorageState of the associated Conveyor Position

  const bool ballDetected = false;

  std::shared_ptr<frc::DigitalInput> ballPosition0;
  std::shared_ptr<frc::DigitalInput> ballPosition1;
  std::shared_ptr<frc::DigitalInput> ballPosition2;
  std::shared_ptr<frc::DigitalInput> ballPosition3;
  std::shared_ptr<frc::DigitalInput> ballPosition4;
  std::shared_ptr<frc::DigitalInput> ballPosition5;

  std::shared_ptr<rev::CANSparkMax> intakeSpark;
  std::shared_ptr<rev::CANSparkMax> armSpark;

  std::shared_ptr<rev::CANSparkMax> primaryConveyorSpark;
  std::shared_ptr<rev::CANSparkMax> followerConveyorSpark;
};