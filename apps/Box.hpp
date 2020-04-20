//
// Created by tejes on 4/19/2020.
//

#ifndef FINALPROJECT_BOX_HPP
#define FINALPROJECT_BOX_HPP
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2World.h>

#include <cinder/app/App.h>

#include <cinder/app/App.h>
#include <glm/detail/type_vec2.hpp>
#include <glm/glm.hpp>
class Box {
  b2World* world_;
  b2Vec2 box_position_;
  b2Body* body;
  b2FixtureDef fixture;
  float mVel;
  float mRadius;
  glm::vec2 mLoc;
  glm::vec2 mDir;

 public:
  void update();
  void draw();
  Box(glm::vec2 loc);
  b2Body* CreateBody(b2World* my_world, glm::vec2& position,
                     glm::vec2& dimensions);
};

#endif  // FINALPROJECT_BOX_HPP
