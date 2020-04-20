// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace myapp {
using namespace cinder;
using cinder::app::KeyEvent;
int c = 0; int k = 0;
vec2 pos;
vec2 dimension;
Box box();
MyApp::MyApp() { }

void MyApp::setup() {
    //Setup gets called once
    k++;
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
    pos = vec2(0.0f, 4.0f);
    dimension = vec2(1.0, 1.0);
    //gl::drawSolidRect(Rectf(400, 400, 800,800));
  //  gl::color(0,0,1);

}
int f = 0;
void MyApp::update() {
  //gets called every time
  f++;
  pos = vec2(rand()/10, 5.0f);
  int velocity_iterations = 6;
  int position_iterations = 2;
  float timeStep = 1.0/60.0;
  my_world->Step(timeStep, velocity_iterations, position_iterations);
  gl::clear();
}

void MyApp::draw() {
  //gets called every time
  Box box(my_world, pos, dimension);
  box.CreateBody();
  vec2 pos1(0.2f, 4.0f);
  Box box1(my_world, pos, dimension);
  box1.CreateBody();
  boxes.push_back(box);
  boxes.push_back(box1);
  const int tile_size_ = 50;
  for (auto &boxe : boxes) {
    b2Body* body = boxe.CreateBody();
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    vec2* dimension_b = box.GetBoxDimensions();
    float x_dimension = dimension->x;
    float y_dimension = dimension->y;
    gl::translate(vec2(x_dimension, y_dimension));
    gl::drawSolidRect(Rectf(tile_size_ * position.x, tile_size_ * position.y,
                                                       tile_size_ * position.x +
                                                       tile_size_,
                                                       tile_size_ * position.y+
                                                       tile_size_));
    printf("%4.2f %4.2f %4.2f%4.2d%4.2d%4.2d\n", position.x, position.y, angle,
           c, f, k);
  }

/*

  int velocity_iterations = 6;
  int position_iterations = 2;
  float timeStep = 1.0/60.0;
 // for (int i = 0; i < 60; ++i) {
    my_world->Step(timeStep, velocity_iterations, position_iterations);
    b2Vec2 position = new_body->GetPosition();
    cinder::vec2 position_new(position.x, position.y);
    float angle = new_body->GetAngle();
    c++;
    cinder::gl::drawSolidRect(Rectf(position_new.x + 10, position_new.y + 10,
                                    position_new.x, position_new.y));
    // cinder::gl::drawSolidCircle(position_new, 100);

  //}
*/
}

void MyApp::keyDown(KeyEvent event) {

}

}  // namespace myapp
