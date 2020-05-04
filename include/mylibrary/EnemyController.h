#pragma once
#include <Box2D/Box2D.h>

#include <list>
#include <vector>

#include "Bullet.hpp"
#include "mylibrary/Enemy.h"

class EnemyController {
 public:
  EnemyController();
  // pass the physics world from the main app by reference
  /**Assigns the world to the pointer world_**/
  void setup(b2World &my_world);
  /**Checks if an enemy is dead or not otherwise calls enemy's
   * update function**/
  void update();
  /**Getter for enemies**/
  std::list<Enemy> &GetEnemies();
  /**Draws the enemies**/
  void draw();
  /**Adds a bullet to the bullets vector**/
  void AddEnemies(int amount);

 private:
  /** store a pointer to the physics world from the main app**/
  b2World *world_;
  /**vector to store the enemies**/
  std::list<Enemy> enemies;
  /**stores the location for testing purposes**/
  b2Vec2 *location_for_test;
  /**This limits the bounce compared to the bullet**/
  const float kBounceLimiter = 20.0f;
  /**Creates the body corresponding to the enemy and adds
   * properties**/
  b2BodyDef &CreateBody(b2BodyDef &bodyDef);
};
