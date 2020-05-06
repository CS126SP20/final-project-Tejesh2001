#pragma once
#include <Box2D/Box2D.h>
#include <cinder/Timer.h>
#include "cinder/Color.h"

namespace mylibrary {
class Enemy {
 public:
  Enemy();
  // pass in a pointer to the particle
  /**Assigns size to enemy for drawing**/
  void setup(const cinder::vec2& boxSize);

  /**Updates the enemy lifecycle**/
  void update();

  /**Draws the enemy**/
  void draw();

  /**Getters and Setter**/
  b2Body* GetBody() const;
  void SetBody(b2Body* body);
  bool IsDead() const;
  void SetIsDead(bool is_dead);

  // store a pointer to the particle
  // in the physics world from the main app
 private:
  /**The body of the enemy*/
  b2Body* body_;

  /**The size to be drawn*/
  ci::vec2 size;

  /**The timespan that the enemy will stay on the screen*/
  int lifespan_;

  /**The initial lifespan*/
  int kLifespan = 60;

  /**The initial age*/
  int kAge = 0;

  /**The age of the enemy (The length of time it has been onscreen
   * **/
  int age_;

  /**timer to decrease lifespan of enemy**/
  cinder::Timer timer_ = true;

  /**Checks if an enemy is dead**/
  bool is_dead_;
};

}  // namespace mylibrary