#include <Box2D/Dynamics/b2World.h>
//
// Created by tejes on 4/30/2020.
//


#ifndef FINALPROJECT_WORLDCREATOR_HPP
#define FINALPROJECT_WORLDCREATOR_HPP

class WorldCreator {
 public:
  void CreateCeiling(b2World &world) const;
  void CreateLeftWall(b2World &world) const;
  void CreateRightWall(b2World &world) const;
};

#endif  // FINALPROJECT_WORLDCREATOR_HPP
