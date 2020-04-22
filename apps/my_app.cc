// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "CoordinateConversions.h"
#include "Engine.hpp"
#include "ParticleController.h"
#include "cinder/app/AppBase.h"
#include "direction.h"

// TODO RANDOMISE SPACING
///ADD PLAYER
///ADD BULLET TO GET RID OF STUFF
///ADD GAME OVER WHEN IT PILES UP
///ADD CLEAR SCREEN MECHANISM
///TRY AND FIGURE OUT CARTESIAN SYSTEM ORIGIN
///HAVE TO DO PLAYER.SETLOCATION FOR BEGINING


namespace myapp {

using cinder::app::KeyEvent;
b2Vec2 gravity(1.0f, 0.0f);
b2World world_(gravity);
particles::ParticleController particleController;
Engine engine_;
Player player_;
void MyApp::setup() {
  is_mouse_pressed_ = false;
  // first define a ground box (no mass)
  // 1. define a body
  //TODO VERTICAL FLOOR HAS BEEN REMOVED TEMPORARILY
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(
      conversions::ToBox2DCoordinates(cinder::app::getWindowWidth()),
      conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()/2));
  // pos of ground

  // 2. use world to create body
  b2Body* groundBody = world_.CreateBody(&groundBodyDef);

  // 3. define fixture
  b2PolygonShape groundBox;
  groundBox.SetAsBox(conversions::ToBox2DCoordinates(1.0f),
      conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()/2));
  player_.SetLoc(getWindowCenter());
  engine_.SetInitialPosition(getWindowCenter());
  // size the ground

  // 4. create fixture on body
  groundBody->CreateFixture(&groundBox, 0.0f);

  // pass world to ParticleController
  timer_.start(0);
  particleController.setup(world_);

  player_.SetLoc(getWindowCenter());
  engine_.SetInitialPosition(getWindowCenter());
}

void MyApp::update() {

  if (is_mouse_pressed_)
    particleController.addParticle(mouse_position_);

  if (timer_.getSeconds() - kTimeChange >= kDoubleEqualityChecker) {
    particleController.addParticles(5);
    particleController.update();
    timer_.start(0.0);
  }

  // Move physics world
  float time_step = 1.0f / 60.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
 world_.Step(time_step, velocity_iterations, position_iterations);
}

void MyApp::draw() {
  cinder::gl::clear(cinder::Color( 0, 0, 0 ));
  cinder::gl::enableAlphaBlending();
  player_.draw();
 // particleController.draw();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine_.DirectionToMove(Direction::kUp);
      engine_.Move();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine_.DirectionToMove(Direction::kDown);
      engine_.Move();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine_.DirectionToMove(Direction::kLeft);
      engine_.Move();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine_.DirectionToMove(Direction::kRight);
      engine_.Move();
      break;
    }
    case KeyEvent::KEY_r: {
      //ResetGame();
      break;
    }
  }
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
