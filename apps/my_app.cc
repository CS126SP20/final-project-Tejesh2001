// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <ciAnimatedGif.h>
#include <cinder/gl/gl.h>

#include "Bullet.hpp"
#include "CoordinateConversions.h"
#include "ParticleController.h"
#include "cinder/app/AppBase.h"
#include "direction.h"
#include "engine.h"

// TODO RANDOMISE SPACING
///ADD BULLET TO GET RID OF STUFF
///ADD GAME OVER WHEN IT PILES UP
///ADD CLEAR SCREEN MECHANISM
///TRY AND FIGURE OUT CARTESIAN SYSTEM ORIGIN
///Crop sprite picture for aesthetitcs // Kinda got it?
///ADD WAVE INCOMING SIGNS AND THEN USE REMOVE ALL. PAUSE THE GAME FIRST
///USE A TIMER


///Immediate stuff
///Add location check for game End with player location (Implemented. Figure
// out print text now
///Add a bullet class
///Tie it the player position as a starting position
///Commit 4 - add description = remove block from screen in development md
int number_of_particles_ = 5;
namespace myapp {

using cinder::app::KeyEvent;
b2Vec2 gravity(0, 100.0f);
cinder::Timer timer_enemy;
b2World world_(gravity);
Player player_(b2Vec2(400, 400));
Engine engine_(player_);
ParticleController particleController;
std::vector <Bullet> bullets;
MyApp::MyApp() {
}

void MyApp::setup() {
  is_mouse_pressed_ = false;
  // first define a ground box (no mass)
  // 1. define a body
  //TODO VERTICAL FLOOR HAS BEEN REMOVED TEMPORARILY
 b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(
      conversions::ToBox2DCoordinates(cinder::app::getWindowWidth()/2),
     0.0);
  // pos of ground

  // 2. use world to create body
  b2Body* groundBody = world_.CreateBody(&groundBodyDef);

  // 3. define fixture
  b2PolygonShape groundBox;

//  printf("No of bullets %f \n", b->getBody()->GetPosition().y);

  groundBox.SetAsBox(conversions::ToBox2DCoordinates
  (cinder::app::getWindowWidth()), 1);
  //engine_.SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  b2FixtureDef fixture_def;
  groundBody->CreateFixture(&groundBox, 0.0);

  // pass world to ParticleController
  timer_.start(0);
  timer_enemy.start(0);
  particleController.setup(world_);
//  particleController.addParticles(1);

 // player_.SetLoc(getWindowCenter());
  //engine_.SetInitialPosition(getWindowCenter());
}
int c = 0;
void MyApp::update() {
  /*if (is_mouse_pressed_) {
   // particleController.addParticle(mouse_position_);
   const b2Vec2 loc = engine_.GetPlayer().GetLoc();
   Bullet bullet(world_, loc);
   bullet.CreateBody(world_);
  }*/

  if (timer_.getSeconds() - kTimeChange >= kDoubleEqualityChecker) {
    number_of_particles_ += 1;
    particleController.addParticles(number_of_particles_);
   // particleController.addParticles(1);
    timer_.start(0.0);
  }
  // Move physics world
 // bullets.clear();
  if (is_mouse_pressed_) {
    // particleController.addParticle(mouse_position_);
    const b2Vec2 loc = engine_.GetPlayer().GetLoc();
    Bullet bullet(world_, loc);
    bullet.CreateBody(world_);
    bullets.push_back(bullet);
  }
  if (!bullets.empty())
  printf("bullet location %f \n", (bullets[0].getBody()
                                     ->GetPosition()).y);
  engine_.Step(world_, particleController, number_of_particles_);
 /* for (auto b = bullets.begin();
          b != bullets.end();) {
    if (!bullets.empty() &&
        b->getBody()->GetPosition().y >=
            conversions::ToBox2DCoordinates(getWindowHeight() - 1)) {
      printf("No of bullets %f \n", b->getBody()->GetPosition().y);
      world_.DestroyBody(b->getBody());
      b = bullets.erase(b);
    } else {
      ++b;
    }
  }*/
  if (!bullets.empty()) {
    for (Bullet bullet : bullets) {
      bullet.update(bullets);
    }
  }

    /* if (!bullets.empty()) {
       printf("bullet location x and y %f %f \n", bullets[0].getBody()
   ->GetPosition().x, bullets[0].getBody()
           ->GetPosition().y);
     }*/
  //printf("No of bullets outside the conditoion %d \n", bullets.size());
 //engine_.Step(world_, particleController, number_of_particles_);
  particleController.update();
}

void MyApp::draw() {
  cinder::gl::clear(cinder::Color( 0, 0, 0 ));
  cinder::gl::enableAlphaBlending();
  DrawBackground();
  DrawPlayer();
  for (Bullet bullet : bullets) {
    bullet.draw();
  }

 // printf("No of bullets %d \n", bullets.size());
  /*if (!bullets.empty())
  bullets[bullets.size() - 1].draw();*/

 // printf("No of bullets %i \n", bullets.size());
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
  if (event.isRightDown()) {
    // particleController.addParticle(mouse_position_);
    const b2Vec2 loc = engine_.GetPlayer().GetLoc();
    Bullet bullet(world_, loc);
    bullet.CreateBody(world_);
    bullets.push_back(bullet);
  //  is_mouse_pressed_ = true;
  }
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
    const b2Vec2 loc = engine_.GetPlayer().GetLoc();
    cinder::fs::path path = cinder::fs::path("avatar.gif");
   // printf ("location current %f %f\n", loc.x, loc.y);
    cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
        loadImage(cinder::app::loadAsset(path)));
    cinder::gl::draw(texture, Rectf( loc.x,
                                    loc.y, loc.x + 2 * tile_size_, loc.y +
                                    2*tile_size_));
}
  void MyApp::DrawBackground() {
    cinder::fs::path path = cinder::fs::path("background.jpg");
    cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
        loadImage(cinder::app::loadAsset(path)));
    cinder::gl::draw(texture, Rectf(getWindowBounds()));
  }
  }  // namespace myapp
