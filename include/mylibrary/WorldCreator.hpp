#include <Box2D/Dynamics/b2World.h>
//
// Created by tejes on 4/30/2020.
//
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "CoordinateConversions.h"
#include "ProjectWideConstants.h"
#ifndef FINALPROJECT_WORLDCREATOR_HPP
#define FINALPROJECT_WORLDCREATOR_HPP

class WorldCreator {
 public:
  void CreateCeiling(b2World &world);
  void CreateLeftWall(b2World &world);
  void CreateRightWall(b2World &world);

 private:
  float right_most_index_;
  float upper_most_index_;
  const double density = 0.0;
  /**This function initiliases indexes to 800 for testing, and otherwise to
   * window characterestics **/
  void TestCheck(b2World &world);
  /**Gets Wall thickness**/
  auto GetWallDimension() const -> float;
};

#endif  // FINALPROJECT_WORLDCREATOR_HPP
