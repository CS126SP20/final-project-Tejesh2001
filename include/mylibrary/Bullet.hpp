//
// Created by tejes on 4/25/2020.
//

#ifndef FINALPROJECT_BULLET_HPP
#define FINALPROJECT_BULLET_HPP

#include <Box2D/Dynamics/b2World.h>
#include <cinder/Cinder.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <vector>
class Bullet {
 public:
  /**Bullet constructor*/
  Bullet();
  /**Sets he body for the bullet*/
  void SetBody(b2Body* body);
  /**Renders bullet on screen*/
  void draw();
  /**Getter for Body*/
  b2Body* GetBody();
 private:
  b2Body* body_;
};

#endif  // FINALPROJECT_BULLET_HPP
