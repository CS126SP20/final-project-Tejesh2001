//
// Created by tejes on 4/22/2020.
//

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "CoordinateConversions.h"
#include "Engine.hpp"
#include "ParticleController.h"
#include "cinder/app/AppBase.h"
#include "Engine.hpp"
vec2 Engine::DirectionToMove(Direction direction) {
  direction_ = direction;
  if (direction == Direction::kUp) {
    return {0, -50};
  }
  if (direction == Direction::kDown) {
    return {0, 50};
  }
  if (direction == Direction::kRight) {
    return {50, 0};
  }
  if (direction == Direction::kLeft) {
    return {-50, 0};
  }

}
void Engine::Move() {
  vec2 move_by = DirectionToMove(direction_);
  vec2 new_location = player_.GetLocation() + move_by;
  player_ .SetLoc(new_location);
  //player_.draw();
  cinder::fs::path path = cinder::fs::path("T.jpg");
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(myapp::loadAsset(path)));
  //cinder::gl::pushMatrices();
  /*if (draw_first) {
    //MovePlayer(loc);
    draw_first = false;
  }*/
  cinder::gl::draw(texture, Rectf(new_location.x, new_location.y,
      new_location.x + 300,
      new_location.y +
  400));

  //player_.MovePlayer(move_by);
}
void Engine::SetInitialPosition(const vec2& location) {
  player_.SetLoc(location);
}
