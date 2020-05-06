#pragma once
#include "mylibrary/EnemyController.h"
#include <cinder/app/AppBase.h>
#include "cinder/Rand.h"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/ProjectWideConstants.h"

namespace mylibrary {
using std::list;
EnemyController::EnemyController() = default;

void EnemyController::setup(b2World &my_world) {
  // Setting up world and location for test
  world_ = &my_world;
  location_for_test = new b2Vec2(0, 0);
}

void EnemyController::update() {
  for (auto p = enemies.begin(); p != enemies.end();) {
    // if the enemy is dead, it removes the body
    if (!enemies.empty() && p->IsDead()) {
      world_->DestroyBody(p->GetBody());
      p = enemies.erase(p);
    } else {
      p->update();
      ++p;
    }
  }
}

void EnemyController::draw() {
  for (auto &particle : enemies) {
    particle.draw();
  }
}

void EnemyController::AddEnemies(int amount) {
  int kTestAmount = 3;
  // I add 3 enemies in my test cases there test amount is three
  float world_width;
  if (amount <= kTestAmount) {
    world_width = global::kLeftMostIndex;
  } else {
    world_width = (conversions::ToBox2DCoordinates(
        static_cast<float>(cinder::app::getWindowWidth())));
  }

  for (int i = 0; i < amount; i++) {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    // Sets the position of the enemy on top of the screen somewhere
    if (location_for_test->y != global::kLowerMostIndex) {
      body_def.position.Set(ci::randFloat(world_width),
                            global::kLowerMostIndex);
    } else {
      body_def.position.Set(location_for_test->x, location_for_test->y);
      location_for_test->y = kActualY;
    }
    CreateBody(body_def);
  }
}

b2BodyDef &EnemyController::CreateBody(b2BodyDef &body_def) {
  Enemy enemy;
  // Creating enemy and its corresponding properties
  body_def.userData = &enemy;
  body_def.bullet = true;
  enemy.SetBody(world_->CreateBody(&body_def));
  b2PolygonShape dynamic_box;

  // Setting dimensions of enemy
  dynamic_box.SetAsBox(
      conversions::ToBox2DCoordinates(global::kBoxDimensions.x),
      conversions::ToBox2DCoordinates(global::kBoxDimensions.y));
  b2FixtureDef fixture_def;

  // Setting properties of fixture
  fixture_def.shape = &dynamic_box;
  fixture_def.density = global::kDensity;
  fixture_def.friction = global::kFriction;
  fixture_def.restitution = global::kRestitution / kBounceLimiter;  // bounce

  // Setting body properties
  enemy.GetBody()->CreateFixture(&fixture_def);
  enemy.setup(global::kBoxDimensions);
  enemies.push_back(enemy);
  return body_def;
}
std::list<Enemy> &EnemyController::GetEnemies() { return enemies; }
}  // namespace mylibrary
