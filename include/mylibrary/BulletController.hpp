//
// Created by tejes on 4/26/2020.
//

#ifndef FINALPROJECT_BULLETCONTROLLER_HPP
#define FINALPROJECT_BULLETCONTROLLER_HPP

#include <Box2D/Dynamics/b2World.h>

#include "Bullet.hpp"
class BulletController {
 public:
  BulletController();
  /**Assigns the world to the pointer world_**/
  void setup(b2World& my_world);
  /**Adds a bullet to the bullets vector**/
  void addBullet(const b2Vec2 player_pos);
  /**Getter for bullets**/
  std::vector<Bullet>& GetBullets();
  /**Checks if a bullet is dead or not**/
  void update();
  /**Draws the bullet**/
  void draw();

 private:
  /**Holds all the bullets**/
  std::vector<Bullet> bullets;
  /**Creates the body of the bullet and all associated properties**/
  b2BodyDef& CreateBody(b2BodyDef& body_def);
  /**linear velocity of the bullet**/
  static const int kBulletVelocity = -50;
  /**world pointer**/
  b2World* world_;
};

#endif  // FINALPROJECT_BULLETCONTROLLER_HPP