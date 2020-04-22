
#include "player.h"
void Player::draw() {
  cinder::fs::path path = cinder::fs::path("T.jpg");
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(myapp::loadAsset(path)));
  //cinder::gl::pushMatrices();
  /*if (draw_first) {
    //MovePlayer(loc);
    draw_first = false;
  }*/
  cinder::gl::draw(texture, Rectf(loc.x, loc.y, loc.x + 50, loc.y + 50));
  std::cout <<  loc.x;
  //cinder::gl::popMatrices();
}
void Player::MovePlayer(const vec2& vec) {
  //gl::translate(vec);
  draw();
}
