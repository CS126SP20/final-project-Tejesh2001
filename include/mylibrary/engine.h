// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H_
#define FINALPROJECT_ENGINE_H_
#include <Box2D/Dynamics/b2World.h>
#include <random>
#include <set>
#include "Bullet.hpp"
#include "EnemyController.h"
#include "direction.h"
#include "mylibrary/player.h"

namespace mylibrary {

// This is the game engine which is the primary way to interact with the game.
class Engine {
 public:
  explicit Engine(Player player);
  /** Changes the direction of the player for the next time step*/
  void SetDirection(Direction);

  /**Sets the direction of the player**/
  auto FromDirection(const Direction direction) -> b2Vec2;

  /**Getter for player**/
  auto GetPlayer() const -> Player;

  /**Sets location of player on Screen*/
  void SetLocation();

  /** Executes a time step: checks for collisions.*/
  void Step(b2World& world, EnemyController& enemy_controller,
            std::vector<Bullet>& bullets);

  /**Getter to check if game is over or not**/
  bool GetIsGameOver();

  /**Find's if a bullet collided with an enemy. If it did, it updates
   * the game score */
  void FindBulletCollision(EnemyController& enemy_controller,
                           const std::vector<Bullet>& bullets);

  /**Gets the game score**/
  int Engine::GetGameScore();

  /**Gets the number of lives**/
  int GetLives();

 private:
  /**Sets direction of the player*/
  Direction direction_;

  /**Sets player object*/
  Player player_;

  /**boolean to check if the game is over*/
  bool is_game_over_;

  /**Check if a player collided with an object*/
  void FindPlayerCollision(const std::list<Enemy>& enemy_list);

  /**Updates the score of the game*/
  int game_score_;

  /**Number of lives**/
  int lives_;
};

}  // namespace mylibrary

#endif  // FINALPROJECT_ENGINE_H_
