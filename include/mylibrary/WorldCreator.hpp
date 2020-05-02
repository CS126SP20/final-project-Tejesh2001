#include <Box2D/Dynamics/b2World.h>
//
// Created by tejes on 4/30/2020.
//

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "CoordinateConversions.h"
#include "ProjectWideVariables.h"
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
  void TestCheck(b2World &world);
};

#endif  // FINALPROJECT_WORLDCREATOR_HPP
