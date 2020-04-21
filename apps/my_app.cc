// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>
#include "Conversions.h"
#include "ParticleController.h"
#include "cinder/app/AppBase.h"

namespace myapp {

using cinder::app::KeyEvent;
b2Vec2 gravity(1.0f, 0.0f);
b2World world_(gravity);
particles::ParticleController particleController;
void MyApp::setup() {
  is_mouse_pressed_ = false;
  // first define a ground box (no mass)
  // 1. define a body
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(
      Conversions::toPhysics(cinder::app::getWindowWidth() / 2),
      Conversions::toPhysics(cinder::app::getWindowHeight()));  // pos of ground

  // 2. use world to create body
  b2Body* groundBody = world_.CreateBody(&groundBodyDef);

  // 3. define fixture
  b2PolygonShape groundBox;
  groundBox.SetAsBox(Conversions::toPhysics(cinder::app::getWindowWidth() / 2),
                     Conversions::toPhysics(1.0f));  // size the ground

  // 4. create fixture on body
  groundBody->CreateFixture(&groundBox, 0.0f);

  // pass world to ParticleController
  timer_.start(0);
  particleController.setup(world_);
}

void MyApp::update() {

  if (is_mouse_pressed_)
    particleController.addParticle(mouse_position_);

  if (timer_.getSeconds() - kTimeChange >= kDoubleEqualityChecker) {
    particleController.addParticles(5);
    particleController.update();
    timer_.start(0.0);
  }

  // step physics world
  float time_step = 1.0f / 60.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
  world_.Step(time_step, velocity_iterations, position_iterations);
}

void MyApp::draw() {
  cinder::gl::clear(cinder::Color( 0, 0, 0 ));
  cinder::gl::enableAlphaBlending();
  particleController.draw();
}

void MyApp::keyDown(KeyEvent event) {
  return;

}
void MyApp::mouseDown(cinder::app::MouseEvent event) {
    is_mouse_pressed_ = true;
}
  void MyApp::mouseMove(cinder::app::MouseEvent event) {
    mouse_position_ = event.getPos();
    //This is for implementing player shooting speed later on
    mouse_velocity_ = ( event.getPos() - mouse_position_);
  }
  void MyApp::mouseDrag(cinder::app::MouseEvent event) { mouseMove(event); }
  void MyApp::mouseUp(MouseEvent event) { is_mouse_pressed_ = false; }

  }  // namespace myapp
