//
// Created by tejes on 4/25/2020.
//

#include "mylibrary/Bullet.hpp"

#include <Box2D/Box2D.h>

#include "mylibrary/ProjectWideConstants.h"

namespace mylibrary {

Bullet::Bullet() { is_dead_ = false; }

void Bullet::draw() {
  // This gives the onscreen position(in pixels)
  ci::vec2 pos = conversions::ToScreen(body_->GetPosition());
  // This gets the rotation of box2D
  float t = conversions::RadiansToDegrees(body_->GetAngle());
  ci::gl::pushMatrices();
  ci::gl::translate(pos);
  ci::gl::rotate(t);
  ci::Rectf rect(-global::kBoxDimensions.x, -global::kBoxDimensions.y,
                 global::kBoxDimensions.x, global::kBoxDimensions.y);
  auto load = loadImage(cinder::app::loadAsset("airball.png"));
  cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(load);
  cinder::gl::draw(image, rect);
  ci::gl::popMatrices();
}

void Bullet::update() {
  // The first part of the if condition is for testing
  if (body_->GetPosition().y >=
          conversions::ToBox2DCoordinates(global::kBoundsOfWindow) ||
      body_->GetPosition().y >=
          conversions::ToBox2DCoordinates(
              static_cast<float>(ci::app::getWindowHeight()))) {
    is_dead_ = true;
  }
}

b2Body *Bullet::GetBody() { return body_; }
void Bullet::SetBody(b2Body *body) { body_ = body; }
bool Bullet::GetIsDead() const { return is_dead_; }
void Bullet::SetIsDead(bool is_dead) { is_dead_ = is_dead; }

}  // namespace mylibrary
