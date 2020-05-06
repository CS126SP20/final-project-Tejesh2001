//
// Created by tejes on 4/30/2020.
//

#include "mylibrary/WorldCreator.hpp"

namespace mylibrary {

void WorldCreator::CreateCeiling(b2World& world) {
  TestCheck(world);
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(right_most_index_, -kWallThickness);
  // 2. use world to create body
  b2Body* ground_body = world.CreateBody(&ground_body_def);
  // 3. define fixture
  b2PolygonShape ground_box;
  ground_box.SetAsBox(right_most_index_, kWallThickness);
  // size the ground
  // 4. create fixture on body
  ground_body->CreateFixture(&ground_box, density);
}

void WorldCreator::CreateLeftWall(b2World& world) {
  TestCheck(world);
  b2BodyDef wall_left;
  wall_left.position.Set(global::kLeftMostIndex, upper_most_index_);
  b2Body* wall_body = world.CreateBody(&wall_left);
  // 3. define fixture
  b2PolygonShape wall_box;
  wall_box.SetAsBox(kWallThickness, right_most_index_);
  // engine_->SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  wall_body->CreateFixture(&wall_box, density);
}
void WorldCreator::CreateRightWall(b2World& world) {
  TestCheck(world);
  b2BodyDef wall_right;
  wall_right.position.Set(right_most_index_, upper_most_index_);
  // pos of ground

  // 2. use world to create body
  b2Body* wall_body = world.CreateBody(&wall_right);

  // 3. define fixture
  b2PolygonShape wall_box;
  wall_box.SetAsBox(kWallThickness, right_most_index_);
  // size the ground
  // 4. create fixture on body
  wall_body->CreateFixture(&wall_box, density);
}
void WorldCreator::TestCheck(b2World& world) {
  if (world.GetGravity().y == 0.0f) {
    // This condition is required for testing
    right_most_index_ = conversions::ToBox2DCoordinates(
        static_cast<float>(global::kBoundsOfWindow - global::kScalingFactor));
    upper_most_index_ = conversions::ToBox2DCoordinates(
        static_cast<float>(global::kBoundsOfWindow));
  } else {
    right_most_index_ = conversions::ToBox2DCoordinates(
        static_cast<float>(ci::app::getWindowWidth()));
    upper_most_index_ = conversions::ToBox2DCoordinates(
        static_cast<float>(ci::app::getWindowHeight()) -
        global::kScalingFactor);
  }
}
}  // namespace mylibrary
