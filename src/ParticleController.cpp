#pragma once
#include "mylibrary/ParticleController.h"

#include <cinder/app/AppBase.h>

#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/Particle.h"
#include "mylibrary/ProjectWideVariables.h"

using namespace ci;
using std::list;


ParticleController::ParticleController()= default;;
void ParticleController::setup(b2World &my_world)
{
  world_ = &my_world;
}
void ParticleController::update()
{
  for (auto p = particles.begin();
  p != particles.end();) {
    if (!particles.empty() && p->IsDead()) {
     world_->DestroyBody(p->GetBody());
     p = particles.erase(p);
    } else {
      p->update();
      ++p;
    }

    }
  /*if (particles.size() > 20) {
    for (int i = 0; i < 5; i++) {
    world_->DestroyBody(particles.begin()->body);
    particles.pop_front();
    }
  }*/

  //Used for enemies later on
  wave_controller++;
}

void ParticleController::draw()
{
  for(auto &particle : particles){
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
{/*
  for(auto & particle : particles) {
    world_->DestroyBody(particle.body);
  }
  particles.clear();
  if (global::color_change == 0)
    global::color_change++;
  else
    global::color_change--;
    */
}


void ParticleController::addParticles(int amount) {
  float world_width =
      (conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()));
  float enemy_spacing = world_width / amount;
  float x_index = 0.0f;
  for (int i = 0; i < amount; i++) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    x_index += enemy_spacing;
    bodyDef.position.Set(randFloat(world_width), 0.0f);
    if (x_index > world_width) {
      break;
    }
    // corresponding particle
    CreateBody(bodyDef);
  }
}
b2BodyDef &ParticleController::CreateBody(b2BodyDef &bodyDef) {
  Particle enemy;
  bodyDef.userData = &enemy;
  bodyDef.bullet = true;
  enemy.SetBody(world_->CreateBody(&bodyDef));
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
  particles.push_back(enemy);
  return bodyDef;
}
 std::list<Particle> &ParticleController::GetParticles() {
  return particles;
}
/*void ParticleController::CheckForCollisionWithBullet(Bullet bullet) {

  for (auto particle = particles.begin();
       particle != particles.end();) {
    printf("bullet location %d \n",
           static_cast<int>(bullet.getBody()->GetPosition().y));
    printf("particle location %d \n",
           static_cast<int>((particle->GetBody()
               ->GetPosition().y)));
    if (static_cast<int>(bullet.getBody()->GetPosition().x) ==
        static_cast<int>((particle->GetBody()->GetPosition().x))
        &&
        static_cast<int>(bullet.getBody()->GetPosition().y) ==
        static_cast<int>((particle->GetBody()->GetPosition().y))) {

      printf("bullet location %d \n",
             static_cast<int>(bullet.getBody()->GetPosition().y));
      printf("particle location %d \n",
             static_cast<int>((particle->GetBody()
                 ->GetPosition().y)));
      world_->DestroyBody(particle->GetBody());
      particle = particles.erase(particle);
     // exit(6);
      break;
      // particle_controller.update();
      break;
      exit(6);
    } else {
      //  particle->update();
      ++particle;
    }
  }*/
}
