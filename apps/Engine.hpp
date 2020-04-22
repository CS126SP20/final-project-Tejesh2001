//
// Created by tejes on 4/22/2020.
//

#ifndef FINALPROJECT_ENGINE_HPP
#define FINALPROJECT_ENGINE_HPP

#include "direction.h"
#include "player.h"
class Engine {

 private :
  Player player_;
  Direction direction_;
 public :
  vec2 DirectionToMove(Direction direction);
  void Move();
  void SetInitialPosition(const vec2& location);
};

#endif  // FINALPROJECT_ENGINE_HPP
