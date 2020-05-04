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

#include "cinder/app/AppBase.h"
#include "mylibrary/EnemyController.h"
#include "mylibrary/ProjectWideConstants.h"
#include "mylibrary/direction.h"

namespace trials {
b2Vec2 Engine::FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -global::kScalingFactor};
    case Direction::kDown:
      return {0, global::kScalingFactor};
    case Direction::kLeft:
      return {-global::kScalingFactor, 0};
    case Direction::kRight:
      return {global::kScalingFactor, 0};
  }
  throw std::out_of_range("switch statement not matched");
}

Player Engine::GetPlayer() const { return player_; }


Engine::Engine(Player player) : player_(player) {
  player_.SetLoc(player.GetLoc());
  is_game_over_ = false;
  game_score_ = 0;
  lives_ = 3;
}
void Engine::Step(b2World& world, EnemyController&
enemy_controller, std::vector<Bullet>& bullets) {
  std::list<Enemy> enemy_list = enemy_controller.GetEnemies();

  //Advancing the physics world
  float time_step = 1.0f / 60.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
  world.Step(time_step, velocity_iterations, position_iterations);
  FindBulletCollision(enemy_controller, bullets);
  FindPlayerCollision(enemy_list);
  if (is_game_over_) {
    return;
  }
  is_game_over_ = false;
  return;
}
void Engine::FindPlayerCollision(const std::list<Enemy>& enemy_list) {

  //Correlates player position with enemy position. If found, it is game over
  for (auto& particle : enemy_list) {
    cinder::vec2 screen_position =
        cinder::vec2(particle.GetBody()->GetPosition().x,
                     particle.GetBody()->GetPosition().y);
    if (static_cast<int>(screen_position.x) ==
            static_cast<int>(GetPlayer().GetLoc().x / global::kScalingFactor) &&
        static_cast<int>(screen_position.y) ==
            static_cast<int>(GetPlayer().GetLoc().y / global::kScalingFactor)) {
      lives_--;
      if (lives_ == 0) {
        is_game_over_ = true;
      }
    }
  }
}
void Engine::FindBulletCollision(EnemyController& enemy_controller,
                                 const std::vector<Bullet>& bullets)  {

  //This loop goes through all the bullets
  for (Bullet bullet : bullets) {
    if (enemy_controller.GetEnemies().empty()) {
      break;
    }
    //This goes through all the points of contact of each bullet
     for (b2ContactEdge* edge = bullet.GetBody()->GetContactList(); edge;
         edge = edge->next) {
       for (auto enemy = enemy_controller.GetEnemies().begin();
            enemy != enemy_controller.GetEnemies().end();) {
         //This iterates through all the enemies
         //Checks if the edge's fixture is touching the enemy
         if (edge->other == enemy->GetBody() && edge->contact->IsTouching())
         {
           ++game_score_;
           break;
         } else {
           ++enemy;
         }
       }

     }
    }
}

void Engine::SetDirection(const Direction direction) {
  direction_ = direction;
}

void Engine::SetLocation() {
  b2Vec2 d_loc = FromDirection(direction_);
  b2Vec2 loc = (player_.GetLoc() + d_loc);
  player_.SetLoc(loc);
}
bool Engine::GetIsGameOver() { return is_game_over_; }

int Engine::GetGameScore() { return game_score_; }

int Engine::GetLives() { return lives_; }

}  // namespace trials
