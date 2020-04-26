//
// Created by tejes on 4/25/2020.
//

#include "mylibrary/Bullet.hpp"

#include <Box2D/Box2D.h>

#include "mylibrary/ProjectWideVariables.h"

Bullet::Bullet() {}

void Bullet::draw() {

  vec2 pos = conversions::ToScreen( body_->GetPosition() );
  float t = conversions::RadiansToDegrees( body_->GetAngle() );
  gl::pushMatrices();
  gl::translate( pos );
  gl::rotate(t);
//  float box_size_x = Rand::randFloat(global::kBoxXMin, global::kBoxXMax);
//  float box_size_y = Rand::randFloat(global::kBoxYMin, global::kBoxYMax);
  //vec2 size = vec2(box_size_x, box_size_y);
  Rectf rect(-global::kBoxDimensions.x,
             -global::kBoxDimensions.y,
             global::kBoxDimensions.x, global::kBoxDimensions.y);
  auto load = loadImage(cinder::app::loadAsset("air.png"));
  cinder::gl::Texture2dRef image =
      cinder::gl::Texture2d::create(load);
  cinder::gl::draw(image, rect);
  gl::popMatrices();

}


b2Body *Bullet::getBody() const { return body_; }
void Bullet::SetBody(b2Body *body) {
  body_ = body;
}

