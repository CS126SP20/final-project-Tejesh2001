//
// Created by tejes on 4/25/2020.
//

#include "Bullet.hpp"
#include "ProjectWideVariables.h"
#include <Box2D/Box2D.h>

void Bullet::CreateBody(b2World &world) {
  b2BodyDef body_definition;
  body_definition.type = b2_kinematicBody;
  body_definition.position = b2Vec2(conversions::ToBox2DCoordinates(position_
                                                   .x + global::kScalingFactor),
conversions::ToBox2DCoordinates(position_.y + global::kScalingFactor));
  body_ = world_->CreateBody(&body_definition);
 // body_->SetBullet(true); This breaks the game idk why
  b2PolygonShape dynamic_box;
  float box_size_x = Rand::randFloat(global::kBoxXMin, global::kBoxXMax);
  float box_size_y = Rand::randFloat(global::kBoxYMin, global::kBoxYMax);
  dynamic_box.SetAsBox(conversions::ToBox2DCoordinates(box_size_x),
                       conversions::ToBox2DCoordinates(box_size_y));
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 0.2f;
  fixture_def.friction = 0.3f;
  fixture_def.restitution = 100.0f;  // bounce
  //fixture_def.isSensor = true;
  body_->SetLinearVelocity(b2Vec2(0, -50));
  body_->CreateFixture(&fixture_def);

  //enemy.setup(vec2(box_size_x, box_size_y));
 // particles.push_back(enemy);
}
Bullet::Bullet(b2World &world, b2Vec2 position) {
  world_ = &world;
  position_ = position;
}
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

void Bullet::update(std::vector<Bullet> &bullets) {

  for (auto b = bullets.begin();
       b != bullets.end();) {
    if (!bullets.empty() &&
        b->getBody()->GetPosition().y >=
        conversions::ToBox2DCoordinates(myapp::getWindowHeight() - 1)) {
      printf("No of bullets %f \n", b->getBody()->GetPosition().y);
      world_->DestroyBody(b->getBody());
      b = bullets.erase(b);
    } else {
      ++b;
    }
  }

};

b2Body *Bullet::getBody() const { return body_; }
