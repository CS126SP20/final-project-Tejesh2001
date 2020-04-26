#pragma once
#include "mylibrary/BulletController.hpp"

#include <cinder/app/AppBase.h>

#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/Particle.h"
#include "mylibrary/ProjectWideVariables.h"

b2World *world_;
using namespace ci;
using std::list;


BulletController::BulletController()= default;

void BulletController::setup(b2World &my_world)
{
  world_ = &my_world;
}
void BulletController::update() {
  for (auto b = bullets.begin();
       b != bullets.end();) {
    if (!bullets.empty() &&
        b->getBody()->GetPosition().y >= 15) {
      //printf("No of bullets %f \n", b->getBody()->GetPosition().y);
      world_->DestroyBody(b->getBody());
      b = bullets.erase(b);
    } else {
      ++b;
    }
  }

}



void BulletController::draw() {
  for(auto &bullet : bullets){
    bullet.draw();
  }
}

void BulletController::addBullet(const b2Vec2 player_pos) {
  // create a dynamic body
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position.Set
      (conversions::ToBox2DCoordinates(player_pos.x + 50),
       conversions::ToBox2DCoordinates(player_pos.y));
  // create body of
  // corresponding particle
  CreateBody(body_def);
}



b2BodyDef &BulletController::CreateBody(b2BodyDef &bodyDef) {
  Bullet bullet;
  bullet.SetBody(world_->CreateBody(&bodyDef));
  bullet.getBody()->SetBullet(true);
  b2PolygonShape dynamic_box;
  float box_size_x = global::kBoxDimensions.x;
  float box_size_y = global::kBoxDimensions.y;//mAKE CONSTANT LATER
  dynamic_box.SetAsBox(conversions::ToBox2DCoordinates(box_size_x),
                       conversions::ToBox2DCoordinates(box_size_y));
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 0.2f;
  fixture_def.friction = 0.3f;
  fixture_def.restitution = 100.0f;  // bounce
  //  fixture_def.isSensor = true;
  bullet.getBody()->SetLinearVelocity(b2Vec2(0, -100));
  //  printf("Bullet linear velocity %f \n", body_->GetLinearVelocity().y);
  bullet.getBody()->CreateFixture(&fixture_def);
  bullets.push_back(bullet);
  return bodyDef;

}
std::vector<Bullet> &BulletController::GetBullets() {
  return bullets;
}

