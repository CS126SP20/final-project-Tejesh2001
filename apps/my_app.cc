// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "CoordinateConversions.h"

#include "ParticleController.h"
#include "cinder/app/AppBase.h"
#include "direction.h"
#include "engine.h"

// TODO RANDOMISE SPACING
///ADD PLAYER
///ADD BULLET TO GET RID OF STUFF
///ADD GAME OVER WHEN IT PILES UP
///ADD CLEAR SCREEN MECHANISM
///TRY AND FIGURE OUT CARTESIAN SYSTEM ORIGIN
///HAVE TO DO PLAYER.SETLOCATION FOR BEGINING
///Crop sprite picture for aesthetitcs
///ADD WAVE INCOMING SIGNS AND THEN USE REMOVE ALL. PAUSE THE GAME FIRST
///USE A TIMER


///Immediate stuff
///Add location check for game End with player location (Implemented. Figure
// out print text now
///Add a bullet class
///Tie it the player position as a starting position

int number_of_particles_ = 5;
namespace myapp {

using cinder::app::KeyEvent;
b2Vec2 gravity(0, 100.0f);
b2World world_(gravity);
particles::ParticleController particleController;
myapp::Location loc1(10,10);
Player player_(loc1);
myapp::Engine engine_(player_);
cinder::Timer timer_enemy;
void MyApp::setup() {
  is_mouse_pressed_ = false;
  // first define a ground box (no mass)
  // 1. define a body
  //TODO VERTICAL FLOOR HAS BEEN REMOVED TEMPORARILY
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(
      conversions::ToBox2DCoordinates(cinder::app::getWindowWidth()/2),
      conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()));
  // pos of ground

  // 2. use world to create body
  b2Body* groundBody = world_.CreateBody(&groundBodyDef);

  // 3. define fixture
  b2PolygonShape groundBox;
  groundBox.SetAsBox(conversions::ToBox2DCoordinates(1.0f),
      conversions::ToBox2DCoordinates(cinder::app::getWindowHeight()/2));

  groundBox.SetAsBox(conversions::ToBox2DCoordinates
  (cinder::app::getWindowHeight()/2),
                     conversions::ToBox2DCoordinates(1.0f));
  //engine_.SetInitialPosition(getWindowCenter());
  // size the ground

  // 4. create fixture on body
  groundBody->CreateFixture(&groundBox, 0.0f);

  // pass world to ParticleController
  timer_.start(0);
  timer_enemy.start(0);
  particleController.setup(world_);
  particleController.addParticles(1);

 // player_.SetLoc(getWindowCenter());
  //engine_.SetInitialPosition(getWindowCenter());
}

void MyApp::update() {
  if (is_mouse_pressed_) particleController.addParticle(mouse_position_);

  if (timer_.getSeconds() - kTimeChange >= kDoubleEqualityChecker) {
    number_of_particles_ += 1;
    particleController.addParticles(number_of_particles_);
   // particleController.addParticles(1);
    timer_.start(0.0);
  }
  engine_.Step(world_, particleController, number_of_particles_);
  particleController.update();
}


void MyApp::draw() {
  cinder::gl::clear(cinder::Color( 0, 0, 0 ));
  cinder::gl::enableAlphaBlending();
  DrawPlayer();
  particleController.draw();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine_.SetDirection(Direction::kUp);
      engine_.SetLocation();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kDown);
      engine_.SetLocation();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kLeft);
      engine_.SetLocation();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kRight);
      engine_.SetLocation();
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
  void MyApp::DrawPlayer() {
    int tile_size_ = 50;
    int num_visible = 0;
    const myapp::Location loc = engine_.GetPlayer().GetLoc();
    cinder::fs::path path = cinder::fs::path("T.jpg");
    cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
        loadImage(cinder::app::loadAsset(path)));
    cinder::gl::draw(texture, Rectf(tile_size_ * loc.Row(),
                                    tile_size_ * loc.Col(),
                                    tile_size_ * loc.Row() +
                                    tile_size_,
                                    tile_size_ * loc.Col() +
                                    tile_size_));
}

}  // namespace myapp
