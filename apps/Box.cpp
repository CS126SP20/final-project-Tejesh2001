//
// Created by tejes on 4/19/2020.
//

#include "Box.hpp"
#include <glm/glm.hpp>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

Box::Box(cinder::vec2 loc ) {
  mLoc = loc;
  mDir = cinder::Rand::randVec2();
  mVel = cinder::Rand::randFloat( 5.0f );
  mRadius = 3.0f;
}
void Box::update() {
  mLoc += mDir * mVel;
}
void Box::draw() {
  cinder::gl::drawSolidCircle( mLoc, mRadius );
}
b2Body* Box::CreateBody(b2World* my_world, glm::vec2& position,
                        glm::vec2& dimensions) {
  b2BodyDef define_box_body;
  define_box_body.type = b2_dynamicBody;
  define_box_body.position = b2Vec2(position.x, position.y);
  body = my_world->CreateBody(&define_box_body);
  b2PolygonShape body_shape;
  body_shape.SetAsBox(dimensions.x, dimensions.y);
  fixture.shape = &body_shape;
  fixture.density = 1;
  fixture.friction = 0.5;
  body -> CreateFixture(&fixture);
  return body;
}
