#include "mylibrary/Enemy.h"

#include <Box2D/Box2D.h>
#include <cinder/app/AppBase.h>

#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/ProjectWideVariables.h"

//bool is_dead_ = false;
Enemy::Enemy() {
  is_dead_ = false;
  timer_.start(0);
  age_ = 0;
  lifespan_ = 60;
}

void Enemy::setup(const vec2& boxSize) {
  size = boxSize;
}
void Enemy::update() {
  age_++;
  if ((body_->GetPosition().y >=
       conversions::ToBox2DCoordinates(global::kBoundsOfWindow)) ||
      (age_ != 1 && body_->GetPosition().y >=
                        conversions::ToBox2DCoordinates(
                            static_cast<float>(app::getWindowHeight()))) ||
      age_ > lifespan_) {
    is_dead_ = true;
  }
}

void Enemy::draw() {
  vec2 pos = conversions::ToScreen( body_->GetPosition() );
  float t = conversions::RadiansToDegrees( body_->GetAngle() );
  gl::pushMatrices();
  gl::translate( pos );
  gl::rotate(t);
  Rectf rect(-size.x, -size.y, size.x, size.y);
  auto load = loadImage(cinder::app::loadAsset("fire.png"));
  cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(load);
  cinder::gl::draw(image, rect);
  gl::popMatrices();
}
auto Enemy::GetBody() const -> b2Body* {
  return body_;
}
void Enemy::SetBody(b2Body* body) {
  body_ = body;
}

auto Enemy::IsDead() const -> bool {
  return is_dead_;
}

void Enemy::SetIsDead(bool is_dead) {
  is_dead_ = is_dead;
}
