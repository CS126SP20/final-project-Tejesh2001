#pragma once
#include "mylibrary/EnemyController.h"
#include <cinder/app/AppBase.h>
#include "cinder/Rand.h"
#include "mylibrary/CoordinateConversions.h"

using std::list;

EnemyController::EnemyController(){
}

void EnemyController::setup(b2World &my_world)
{
  world_ = &my_world;
  location_for_test = new b2Vec2(0,0);
}
void EnemyController::update()
{
  for (auto p = enemies.begin();
  p != enemies.end();) {
    if (!enemies.empty() && p->IsDead()) {
     world_->DestroyBody(p->GetBody());
     p = enemies.erase(p);
    } else {
      p->update();
      ++p;
    }

    }
}

void EnemyController::draw()
{
  for(auto &particle : enemies){
    particle.draw();
  }
}


void EnemyController::AddEnemies(int amount) {
 float world_width =
      (conversions::ToBox2DCoordinates(static_cast<float>(
          cinder::app::getWindowHeight())));
  for (int i = 0; i < amount; i++) {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    if (location_for_test->y != 0) {
      body_def.position.Set(randFloat(world_width), 0.0f);
    } else {
      body_def.position.Set(location_for_test->x, location_for_test->x);
      location_for_test->y = -1;
    }
    CreateBody(body_def);
  }
}
b2BodyDef &EnemyController::CreateBody(b2BodyDef &body_def) {
  Enemy enemy;
  //Creating enemy and its corresponding properties
  body_def.userData = &enemy;
  body_def.bullet = true;
  enemy.SetBody(world_->CreateBody(&body_def));
  b2PolygonShape dynamic_box;
  dynamic_box.SetAsBox(conversions::ToBox2DCoordinates(global::kBoxDimensions
                                                           .x),
                      conversions::ToBox2DCoordinates(global::kBoxDimensions
                                                           .y));
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 0.3f;
  fixture_def.friction = 0.3f;
  fixture_def.restitution = 0.5f;  // bounce
  enemy.GetBody()->CreateFixture(&fixture_def);
  enemy.setup(global::kBoxDimensions);
  enemies.push_back(enemy);
  return body_def;
}
 std::list<Enemy> &EnemyController::GetEnemies() {
  return enemies;
}


