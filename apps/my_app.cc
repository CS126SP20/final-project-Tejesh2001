// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include "Box.hpp"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }


void MyApp::setup() {
  b2Vec2 gravity(0, -10);
  my_world = new b2World(gravity);
  //Definitions are not pointers
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0.0, -10.0f);
  //Making the ground body
  b2Body* ground_body =  my_world->CreateBody(&ground_body_def);
  b2PolygonShape ground_box;
  ground_box.SetAsBox(50.0f,10.0f);
  ground_body -> CreateFixture(&ground_box, 0.0f);
  box_controller.addBoxes(50);
}

void MyApp::update() {

  int velocity_iterations = 6;
  int position_iterations = 2;
  float timeStep = 1.0/60.0;
  my_world->Step(timeStep, velocity_iterations, position_iterations);
  box_controller.update();
}

void MyApp::draw() {
 cinder::gl::clear(cinder::Color( 0, 0, 0 ));
 cinder::gl::setMatricesWindow(getWindowWidth(), getWindowHeight());
 box_controller.draw();
}

void MyApp::keyDown(KeyEvent event) { }
void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (event.isRightDown()) {
    box_controller.addBoxes(50);
    Box box(cinder::vec2(0,0));
    cinder::vec2 location(cinder::Rand::randVec2().x,
                 cinder::Rand::randVec2().y);
    cinder::vec2 dimensions(10, 10);
    box.CreateBody(my_world, location, dimensions);
  }
}
void MyApp::mouseMove(cinder::app::MouseEvent event ) {
  mouse_location = event.getPos();
}
void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  mouseMove(event);
}



}  // namespace myapp
