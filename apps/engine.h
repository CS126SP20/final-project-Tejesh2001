// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H_
#define FINALPROJECT_ENGINE_H_

#include <Box2D/Dynamics/b2World.h>

#include <random>
#include <set>

#include "ParticleController.h"
#include "direction.h"
#include "player.h"

namespace myapp {

const int kBoardCoordinate = 5;

// This is the game engine which is primary way to interact with the game.
class Engine {
 public:
  // Creates a new snake game of the given size.
  Engine(size_t width, size_t height);

  // Creates a new snake game of the given size, seeded.
  Engine(size_t width, size_t height, unsigned seed);

  Engine(float x, float y, Player player);
  Engine(Player player);
  // Executes a time step: moves the snake, etc.
 // void Step();

  // Start the game over.
  void Reset();

  // Changes the direction of the snake for the next time step.
  void SetDirection(Direction);

  size_t GetScore() const;


  Player GetPlayer() const;
  void SetLocation();
  void Step(b2World& world, ParticleController& particle_controller,
            int number_of_particles);
 private:
  Location GetRandomLocation();
  std::set<Location> GetOccupiedTiles();

 private:
  Direction direction_;
  std::uniform_real_distribution<double> uniform_;
  Player player_;


};

}  // namespace snake

#endif  // SNAKE_ENGINE_H_
