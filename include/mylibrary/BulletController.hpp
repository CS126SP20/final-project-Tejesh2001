//
// Created by tejes on 4/26/2020.
//

#ifndef FINALPROJECT_BULLETCONTROLLER_HPP
#define FINALPROJECT_BULLETCONTROLLER_HPP

static const int kBulletVelocity = -70;
#include <Box2D/Dynamics/b2World.h>

#include "Bullet.hpp"
class BulletController {
 public:
  BulletController();
  void setup(b2World& my_world);
  void addBullet(const b2Vec2 player_pos);
  std::vector<Bullet>& GetBullets();
  void update();
  void draw();
 private:
  std::vector<Bullet> bullets;
  b2BodyDef& CreateBody(b2BodyDef& bodyDef);
};

#endif  // FINALPROJECT_BULLETCONTROLLER_HPP