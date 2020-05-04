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
  /**Creates the ceiling of the world**/
  void CreateCeiling(b2World &world);
  /**Creates the left wall of the world**/
  void CreateLeftWall(b2World &world);
  /**Creates the right wall of the world**/
  void CreateRightWall(b2World &world);

 private:
  /**The right most index of the walls and ceilings**/
  float right_most_index_;
  /**Upper most index of the walls and ceilings**/
  float upper_most_index_;
  /**Density of wall**/
  const double density = 0.0;
  /**Gets Wall thickness**/
  const float kWallThickness =
      conversions::ToBox2DCoordinates(global::kScalingFactor);
  /**This function initiliases indexes to 800 for testing, and otherwise to
   * window characterestics **/
  void TestCheck(b2World &world);
};

#endif  // FINALPROJECT_WORLDCREATOR_HPP
