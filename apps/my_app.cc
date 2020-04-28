// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
// TODO RANDOMISE SPACING
///TODO MAKE CELING AND WALLS HAVE AN INTERNAL SAME FUNCTION
///Remove the word "using" everywhere
///Fix Development.md
int number_of_particles_ = 5;
namespace myapp {
using cinder::app::KeyEvent;
MyApp::MyApp() {
  b2Vec2 gravity(0, 50.0f);
  max_score_check_ = false;
  number_of_bullets = 0;
  world_ = new b2World(gravity);
  player_ = new Player({getWindowCenter().x, getWindowCenter().y});
  engine_ = new Engine(*player_);
}

void MyApp::setup() {
  is_mouse_pressed_ = false;
  // first define a ground box (no mass)
  // 1. define a body
  CreateCeiling();
  CreateLeftWall();
  CreateRightWall();

  // pass world to enemy_controller_
  timer_.start(0);
  game_timer.start(0);
  enemy_controller_.setup(*world_);
  bullet_controller_.setup(*world_);
//  enemy_controller_.AddEnemies(1);

 // player_.SetLoc(getWindowCenter());
  //engine_->SetInitialPosition(getWindowCenter());
}


void MyApp::CreateCeiling() const {
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(
      conversions::ToBox2DCoordinates(static_cast<float>(app::getWindowWidth())),
     -1.0);
  // 2. use world to create body
  b2Body* ground_body = world_->CreateBody(&ground_body_def);

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
void MyApp::CreateLeftWall() const {

  b2BodyDef wall_left;
  float right_most_index =
      conversions::ToBox2DCoordinates(app::getWindowWidth());
  float upper_most_index =
      conversions::ToBox2DCoordinates(app::getWindowHeight() -
                                      global::kScalingFactor);

  wall_left.position.Set(0.0, upper_most_index);
  b2Body* wall_body = world_->CreateBody(&wall_left);
  // 3. define fixture
  b2PolygonShape wall_box;
  wall_box.SetAsBox(1, right_most_index);
  // engine_->SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  wall_body->CreateFixture(&wall_box, 0.0);
}
void MyApp::CreateRightWall() const {

  b2BodyDef wall_right;
  float right_most_index =
      conversions::ToBox2DCoordinates(app::getWindowWidth());
  float upper_most_index =
      conversions::ToBox2DCoordinates(app::getWindowHeight() - 50);

  wall_right.position.Set(right_most_index, upper_most_index);
  // pos of ground

  // 2. use world to create body
  b2Body* wall_body = world_->CreateBody(&wall_right);

  // 3. define fixture
  b2PolygonShape wall_box;

  //  printf("No of bullets %f \n", b->GetBody()->GetPosition().y);

  wall_box.SetAsBox(1, right_most_index);
  // engine_->SetInitialPosition(getWindowCenter());
  // size the ground
  // 4. create fixture on body
  wall_body->CreateFixture(&wall_box, 0.0);
}
int c = 0;
void MyApp::update() {
  if (game_timer.isStopped()) {
    return;
  }
  //There is a wave of enemies every two seconds. Each wave has one enemy
  // more than the previous one
  if (timer_.getSeconds() - kTimeChange >= kDoubleEqualityChecker) {
    number_of_particles_ += 1;
    enemy_controller_.AddEnemies(number_of_particles_);
    timer_.start(0.0);
  }
  // Move physics world
  engine_->Step(*world_, enemy_controller_,
                                    bullet_controller_.GetBullets());
  bullet_controller_.update();
  enemy_controller_.update();

}

void MyApp::draw() {
  cinder::gl::clear(cinder::Color(0, 0, 0));
  cinder::gl::enableAlphaBlending();
  DrawBackground();
  DrawPlayer();
  bullet_controller_.draw();
  enemy_controller_.draw();
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  if (max_score_check_) {
        PrintText("You have finished your airballs!", color, size,
        vec2(getWindowWidth()/2, getWindowHeight() - global::kScalingFactor));
  }
  if (engine_->GetIsGameOver()) {
    size_t row = 0;
    PrintText("Game Over :(", color, size, center);
    PrintText("Your time was " + std::to_string((game_timer.getSeconds())) +
              " seconds",
              color, size, ivec2(getWindowCenter().x, getWindowCenter().y +
                                 + global::kScalingFactor));
    PrintText("Your score was " + std::to_string(engine_->GetGameScore()),
              color, size, ivec2(getWindowCenter().x, getWindowCenter().y +
                                 2 * global::kScalingFactor));
    game_timer.stop();
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      engine_->SetDirection(Direction::kUp);
      engine_->SetLocation();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      engine_->SetDirection(Direction::kDown);
      engine_->SetLocation();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      engine_->SetDirection(Direction::kLeft);
      engine_->SetLocation();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      engine_->SetDirection(Direction::kRight);
      engine_->SetLocation();
      break;
    }
    case KeyEvent::KEY_RETURN: {
      if (!max_score_check_) {
      AddBullet();
      }
      break;
    }
}

}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  is_mouse_pressed_ = true;
  if (is_mouse_pressed_ && !max_score_check_) {
    AddBullet();
    }
}
void MyApp::AddBullet() {
  const b2Vec2 loc = engine_->GetPlayer().GetLoc();
  bullet_controller_.addBullet(loc);
  number_of_bullets++;
  if (number_of_bullets > kMaxNumberOfBullets) {
    max_score_check_ = true;
  }
}

  void MyApp::mouseUp(MouseEvent event) {
    is_mouse_pressed_ = false;
  }
  void MyApp::DrawPlayer() {
    const b2Vec2 loc = engine_->GetPlayer().GetLoc();
    cinder::fs::path path = cinder::fs::path("avatar.gif");
    cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
        loadImage(cinder::app::loadAsset(path)));
    cinder::gl::draw(texture, Rectf( loc.x,
                                    loc.y, loc.x + 2 * global::kScalingFactor,
                                    loc.y + 2 * global::kScalingFactor));
}
  void MyApp::DrawBackground() {
    cinder::fs::path path = cinder::fs::path("background.jpg");
    cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
        loadImage(cinder::app::loadAsset(path)));
    cinder::gl::draw(texture, Rectf(getWindowBounds()));
  }

template <typename C>
void MyApp::PrintText(const std::string& text, const C& color, const
                         cinder::ivec2&size, const cinder::vec2& loc) {
  cinder::gl::pushMatrices();
  cinder::gl::color(color);
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Ariel", 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);
  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
  cinder::gl::pushMatrices();
}
}  // namespace myapp
