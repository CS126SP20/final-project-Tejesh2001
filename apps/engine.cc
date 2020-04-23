// Copyright (c) 2020 CS126SP20. All rights reserved.

#include "engine.h"

#include <cinder/app/AppBase.h>

#include <algorithm>
#include <cstdlib>
#include <random>
#include <set>
#include <stdexcept>

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
  Location location(cinder::app::getWindowCenter().x, cinder::app::getWindowHeight());
  player_.SetLoc(location);
}

Engine::Engine(Player player) : player_(player) {
  Location location(5, 5);
  player_.SetLoc(location);
}

void Engine::Step() {
  Location d_loc = FromDirection(direction_);
  int height_ = 15;
  int width_ = 15;
  Location new_head_loc =
      (player_.GetLoc() + d_loc) % Location(height_, width_);
  Location leader = new_head_loc;
  player_.SetLoc(leader);
}
void Engine::SetDirection(const Direction direction) {
  direction_ = direction;
}

}  // namespace snake
