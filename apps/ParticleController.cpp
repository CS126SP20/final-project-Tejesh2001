#pragma once
#include "ParticleController.h"

#include <cinder/app/AppBase.h>

#include "CoordinateConversions.h"
#include "ProjectWideVariables.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"

using namespace ci;
using std::list;

namespace particles {


ParticleController::ParticleController(){};
void ParticleController::setup(b2World &my_world)
{
  world_ = &my_world;
}

void ParticleController::update()
{
  /*for( list<Particle>::iterator p = particles.begin();
  p != particles.end(); p++) {
          p->update();
  }*/
  //Used for enemies later on
  wave_controller++;
}

void ParticleController::draw()
{
  for(auto & particle : particles){
    particle.draw();
  }
}

void ParticleController::addParticle(const ivec2 &mouse_pos) {
  // create a dynamic body
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set
      (conversions::ToBox2DCoordinates(mouse_pos.x),
          conversions::ToBox2DCoordinates(mouse_pos.y));
  // create body of
  // corresponding particle
 CreateBody(bodyDef);
}

void ParticleController::removeAll()
{
  for(auto & particle : particles) {
    world_->DestroyBody(particle.body);
  }
  particles.clear();
  if (global::color_change == 0)
    global::color_change++;
  else
    global::color_change--;
}


void ParticleController::addParticles(int amount) {
  float world_y_height =
      (conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()));
  float enemy_spacing = world_y_height / amount;
  float y_index = 0.0f;
  for (int i = 0; i < amount; i++) {
    float world_y_height =
        (conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()));
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    y_index += enemy_spacing;
    bodyDef.position.Set(0.0f, y_index);
    if (enemy_spacing > world_y_height) {
      break;
    }
    // corresponding particle
    CreateBody(bodyDef);
  }
}
b2BodyDef &ParticleController::CreateBody(b2BodyDef &bodyDef) {
  Particle enemy = Particle();
  bodyDef.userData = &enemy;
  enemy.body = world_->CreateBody(&bodyDef);
  b2PolygonShape dynamic_box;
  float box_size_x = Rand::randFloat(global::kBoxXMin, global::kBoxXMax);
  float box_size_y = Rand::randFloat(global::kBoxYMin, global::kBoxYMax);
  dynamic_box.SetAsBox(conversions::ToBox2DCoordinates(box_size_x),
                      conversions::ToBox2DCoordinates(box_size_y));
  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.3f;
  fixture_def.restitution = 0.5f;  // bounce
  enemy.body->CreateFixture(&fixture_def);
  enemy.setup(vec2(box_size_x, box_size_y));
  particles.push_back(enemy);
  return bodyDef;
}

}  // namespace particles