// Copyright (c) 2020 CS126SP20. All rights reserved.

#include "engine.h"

#include <Box2D/Dynamics/b2World.h>
#include <cinder/app/AppBase.h>

#include <algorithm>
#include <cstdlib>
#include <random>
#include <set>
#include <stdexcept>

#include "ParticleController.h"
#include "ProjectWideVariables.h"
#include "direction.h"
#include "location.h"

namespace myapp {

// Converts a direction into a delta location.
Location FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -1};
    case Direction::kDown:
      return {0, 1};
    case Direction::kLeft:
      return {-1, 0};
    case Direction::kRight:
      return {+1, 0};
  }
  throw std::out_of_range("switch statement not matched");
}


Player Engine::GetPlayer() const { return player_; }

void Engine::Reset() {
  Location location(cinder::app::getWindowCenter().x,
      cinder::app::getWindowHeight());
  player_.SetLoc(location);
}

Engine::Engine(Player player) : player_(player) {
  player_.SetLoc(player.GetLoc());
}

void Engine::Step(b2World& world, particles::ParticleController&
particle_controller, int number_of_particles) {
  // Move physics world
  float time_step = 1.0f / 60.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
  world.Step(time_step, velocity_iterations, position_iterations);
  /*std::list<particles::Particle> particle_list = particle_controller
      .GetParticles();*/
  std::vector<Particle> particle_list = particle_controller
      .GetParticles();
  for (Particle particle : particle_list) {
    cinder::vec2 screen_position = cinder::vec2(particle.body->GetPosition().x,
        particle
        .body->GetPosition().y);
  /*  printf("Float value is %d %d\n", GetPlayer().GetLoc().Row(),
           GetPlayer().GetLoc().Col());
    printf("vec2 value is %d %d\n", (int) screen_position.x, (int)
        screen_position.y);*/
    if ((int)screen_position.x == GetPlayer().GetLoc().Row()
        && (int)screen_position.y == GetPlayer().GetLoc().Col()) {
      // cinder::gl::drawSolidCircle(getWindowCenter(), 20);
      _exit(0);
    }
  }
  /*for (int i = 0; i < number_of_particles; i++) {
   // particles::Particle particle = particle_list.back();
   // particle_list.pop_front();
  //  world.DestroyBody(particle.body);
  }
  for (particles::Particle particle : particle_list) {
    particle_list.pop_front();
  }*/

}
void Engine::SetDirection(const Direction direction) {
  direction_ = direction;
}

void Engine::SetLocation() {
  Location d_loc = FromDirection(direction_);
  Location new_head_loc =
      (player_.GetLoc() + d_loc) % Location(global::kPlayerHeight,
          global::kPlayerWidth);
  Location leader = new_head_loc;
  player_.SetLoc(leader);
}

}  // namespace snake
