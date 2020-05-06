#include "mylibrary/Enemy.h"
#include <cinder/app/AppBase.h>
#include "cinder/gl/gl.h"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/ProjectWideConstants.h"

namespace mylibrary {
using cinder::vec2;
Enemy::Enemy() {
  is_dead_ = false;
  timer_.start(0);
  age_ = kAge;
  lifespan_ = kLifespan;
}

void Enemy::setup(const vec2& boxSize) { size = boxSize; }
void Enemy::update() {
  // Increases the age of the enemy every time the update loop is called
  age_++;
  // If it goes off the screen or its age is over then the body is destroyed
  if ((body_->GetPosition().y >=
       conversions::ToBox2DCoordinates(global::kBoundsOfWindow)) ||
      (age_ != 1 && body_->GetPosition().y >=
                        conversions::ToBox2DCoordinates(
                            static_cast<float>(ci::app::getWindowHeight()))) ||
      age_ > lifespan_) {
    is_dead_ = true;
  }
}

void Enemy::draw() {
  // Draws the enemy
  vec2 pos = conversions::ToScreen(body_->GetPosition());
  float t = conversions::RadiansToDegrees(body_->GetAngle());
  ci::gl::pushMatrices();
  ci::gl::translate(pos);
  ci::gl::rotate(t);
  ci::Rectf rect(-size.x, -size.y, size.x, size.y);
  auto load = loadImage(cinder::app::loadAsset("fire.png"));
  cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(load);
  cinder::gl::draw(image, rect);
  ci::gl::popMatrices();
}

auto Enemy::GetBody() const -> b2Body* { return body_; }

void Enemy::SetBody(b2Body* body) { body_ = body; }

auto Enemy::IsDead() const -> bool { return is_dead_; }

void Enemy::SetIsDead(bool is_dead) { is_dead_ = is_dead; }

}  // namespace mylibrary