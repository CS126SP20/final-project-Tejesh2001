// Copyright (c) 2020 CS126SP20. All rights reserved.

#include "mylibrary/engine.h"

#include <Box2D/Dynamics/b2World.h>
#include <cinder/app/AppBase.h>

#include <algorithm>
#include <cstdlib>
#include <mylibrary/Bullet.hpp>
#include <random>
#include <set>
#include <stdexcept>

#include "mylibrary/ParticleController.h"
#include "mylibrary/ProjectWideVariables.h"
#include "mylibrary/direction.h"

namespace myapp {
using namespace global;
// Converts a direction into a delta location.
b2Vec2 FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -kScalingFactor};
    case Direction::kDown:
      return {0, kScalingFactor};
    case Direction::kLeft:
      return {-kScalingFactor, 0};
    case Direction::kRight:
      return {kScalingFactor, 0};
  }
  throw std::out_of_range("switch statement not matched");
}


Player Engine::GetPlayer() const { return player_; }

void Engine::Reset() {
   b2Vec2 location(cinder::app::getWindowCenter().x,
      cinder::app::getWindowHeight());
//  player_.SetLoc(location);
}

Engine::Engine(Player player) : player_(player) {
  player_.SetLoc(player.GetLoc());
}

void Engine::Step(b2World& world, ParticleController&
particle_controller, std::vector<Bullet>& bullets) {
  // Move physics world
  float time_step = 1.0f / 60.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
  world.Step(time_step, velocity_iterations, position_iterations);
  /*std::list<particles::Particle> particle_list = particle_controller
      .GetParticles();*/
  std::list<Particle> particle_list = particle_controller.GetParticles();

  for (auto& particle : particle_list) {
    cinder::vec2 screen_position =
        cinder::vec2(particle.GetBody()->GetPosition().x,
                     particle.GetBody()->GetPosition().y);
    /*printf("Float value is %f %f \n", GetPlayer().GetLoc().x / kScalingFactor,
           GetPlayer().GetLoc().y / kScalingFactor);
    printf("vec2 value is %d %d\n", static_cast<int>(screen_position.x),
           static_cast<int>(screen_position.y));*/
    if (static_cast<int>(screen_position.x) ==
            static_cast<int>(GetPlayer().GetLoc().x / kScalingFactor) &&
        static_cast<int>(screen_position.y) ==
            static_cast<int>(GetPlayer().GetLoc().y / kScalingFactor)) {
      // cinder::gl::drawSolidCircle(getWindowCenter(), 20);
      _exit(0);
    }
  }
    for (Bullet bullet : bullets) {
      if (particle_list.empty()) {
        break;
      }
      particle_controller.CheckForCollisionWithBullet(bullet);
    }
}


void Engine::SetDirection(const Direction direction) {
  direction_ = direction;
}

void Engine::SetLocation() {
  b2Vec2 d_loc = FromDirection(direction_);
  b2Vec2 loc =
      (player_.GetLoc() + d_loc);
  player_.SetLoc(loc);
}

}  // namespace snake
