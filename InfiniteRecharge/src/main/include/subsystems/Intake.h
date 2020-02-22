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

  enum class StorageState {
    PRESENT,
    EMPTY
  };

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
  void TakeIn();
  void PushOut();
  void Stop();
  void ArmUp();
  void ArmDown();
  ArmState GetArmState();
  void RunConveyor();
  void StopConveyor();
  void InventoryPowerCells(); ///set array and then set a counter
  StorageState GetInventory(int position);
  int FirstEmptyPosition();

  ////TODO: add ramp rate?

 private:
  ArmState currentArmState;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  StorageState powerCellPosition[6];

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