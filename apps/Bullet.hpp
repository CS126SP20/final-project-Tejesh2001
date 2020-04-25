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
  b2Body* getBody() const;

 public:
  Bullet(b2World &world, b2Vec2 position);
  void CreateBody(b2World &world);
  void draw();
  void update(std::vector<Bullet> &bullets);


 private:
  b2World* world_;
  b2Vec2 position_;
  b2Body* body_;
};

#endif  // FINALPROJECT_BULLET_HPP
