#pragma once
#include "mylibrary/BulletController.hpp"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/Enemy.h"
#include "mylibrary/ProjectWideConstants.h"

namespace mylibrary {

BulletController::BulletController() = default;

void BulletController::setup(b2World &my_world) { world_ = &my_world; }

void BulletController::update() {
  for (auto b = bullets.begin(); b != bullets.end();) {
    if (!bullets.empty() && b->GetIsDead()) {
      // Destroys bullet once it goes offscreen
      world_->DestroyBody(b->GetBody());
      b = bullets.erase(b);
    } else {
      b->update();
      ++b;
    }
  }
}

void BulletController::draw() {
  for (auto &bullet : bullets) {
    bullet.draw();
  }
}

void BulletController::addBullet(const b2Vec2 player_pos) {
  // create a dynamic body
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position.Set(
      conversions::ToBox2DCoordinates(player_pos.x + global::kScalingFactor),
      conversions::ToBox2DCoordinates(player_pos.y - global::kScalingFactor));
  // create body of
  // corresponding particle
  CreateBody(body_def);
}

b2BodyDef &BulletController::CreateBody(b2BodyDef &body_def) {
  // Creates bullet object and its body
  Bullet bullet;
  bullet.SetBody(world_->CreateBody(&body_def));
  body_def.userData = &bullet;
  b2PolygonShape dynamic_box;
  dynamic_box.SetAsBox(
      conversions::ToBox2DCoordinates(global::kBoxDimensions.x),
      conversions::ToBox2DCoordinates(global::kBoxDimensions.y));

  // Assigning properties to fixtures
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = global::kDensity;
  fixture_def.friction = global::kFriction;
  fixture_def.restitution = global::kRestitution;  // bounce

  // Assigning body properties
  bullet.GetBody()->SetBullet(true);
  bullet.GetBody()->SetLinearVelocity(b2Vec2(0, kBulletVelocity));
  bullet.GetBody()->CreateFixture(&fixture_def);
  bullets.push_back(bullet);
  return body_def;
}

std::vector<Bullet> &BulletController::GetBullets() { return bullets; }

}  // namespace mylibrary