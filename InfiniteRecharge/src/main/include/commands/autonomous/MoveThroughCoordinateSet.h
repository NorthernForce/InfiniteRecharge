/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "commands/autonomous/MoveToCoordinate.h"
#include <vector>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveThroughCoordinateSet
    : public frc2::CommandHelper<frc2::CommandBase, MoveThroughCoordinateSet> {
 public:
  MoveThroughCoordinateSet();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  const std::string coordinateSetLabel = "Coordinate Set";

  std::vector<double> coordinateSet;

  std::unique_ptr<MoveToCoordinate> moveToCoordinate;

  int numOfSets = 0;
  int status = 1;
  int xPos;
  int yPos;
};
