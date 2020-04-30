//
// Created by tejes on 4/30/2020.
//

#include "mylibrary/WorldCreator.hpp"

#include <mylibrary/CoordinateConversions.h>
void WorldCreator::CreateCeiling(b2World& world) const {


  b2BodyDef ground_body_def;
  ground_body_def.position.Set(
      conversions::ToBox2DCoordinates(static_cast<float>(app::getWindowWidth())),
      -1.0);
  // 2. use world to create body
  b2Body* ground_body = world.CreateBody(&ground_body_def);

  // 3. define fixture
  b2PolygonShape ground_box;

  //  printf("No of bullets %f \n", b->GetBody()->GetPosition().y);

  ground_box.SetAsBox(conversions::ToBox2DCoordinates(static_cast<float>
                                                      (app::getWindowWidth
          ())),1);
  // engine_->SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  ground_body->CreateFixture(&ground_box, 0.0);
}
void WorldCreator::CreateLeftWall(b2World& world) const {
  b2BodyDef wall_left;
  float right_most_index =
      conversions::ToBox2DCoordinates
          ((static_cast<float>(app::getWindowWidth())));
  float upper_most_index =
      conversions::ToBox2DCoordinates(static_cast<float>(app::getWindowHeight())
                                      - global::kScalingFactor);

  wall_left.position.Set(0.0, upper_most_index);
  b2Body* wall_body = world.CreateBody(&wall_left);
  // 3. define fixture
  b2PolygonShape wall_box;
  wall_box.SetAsBox(1, right_most_index);
  // engine_->SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  wall_body->CreateFixture(&wall_box, 0.0);


}
void WorldCreator::CreateRightWall(b2World& world) const {


  b2BodyDef wall_right;
  float right_most_index =
      conversions::ToBox2DCoordinates(app::getWindowWidth());
  float upper_most_index =
      conversions::ToBox2DCoordinates(app::getWindowHeight() - 50);

  wall_right.position.Set(right_most_index, upper_most_index);
  // pos of ground

  // 2. use world to create body
  b2Body* wall_body = world.CreateBody(&wall_right);

  // 3. define fixture
  b2PolygonShape wall_box;

  //  printf("No of bullets %f \n", b->GetBody()->GetPosition().y);

  wall_box.SetAsBox(1, right_most_index);
  // engine_->SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  wall_body->CreateFixture(&wall_box, 0.0);
  }
