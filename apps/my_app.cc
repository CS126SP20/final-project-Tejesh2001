// Copyright (c) 2020 [Tejesh Bhaumik]. All rights reserved.

#include "my_app.h"
#include <mylibrary/WorldCreator.hpp>
#include <cinder/audio/Voice.h>
namespace myapp {
using cinder::app::KeyEvent;
cinder::audio::VoiceRef background_audio_file;
MyApp::MyApp() {
  b2Vec2 gravity(0, 80.0f);
  max_score_check_ = false;
  world_ = new b2World(gravity);
  player_ = new Player({app::getWindowCenter().x, app::getWindowCenter().y});
  engine_ = new Engine(*player_);
}

void MyApp::setup() {
  is_mouse_pressed_ = false;
  // first define a ground box (no mass)
  // 1. define a body
  WorldCreator world_creator;
  world_creator.CreateCeiling(*world_);
  world_creator.CreateLeftWall(*world_);
  world_creator.CreateRightWall(*world_);
  // pass world to enemy_controller_
  timer_.start(0);
  game_timer.start(0);
  enemy_controller_.setup(*world_);
  bullet_controller_.setup(*world_);
  PlayBackGroundMusic();
  //  enemy_controller_.AddEnemies(1);

 // player_.SetLoc(getWindowCenter());
  //engine_->SetInitialPosition(getWindowCenter());
}
int c = 0;
void MyApp::update() {
  if (game_timer.isStopped()) {
    return;
  }
  max_score_check_ = bullet_controller_.GetBullets().size() >=
                     kMaxNumberOfBullets;
  //There is a wave of enemies every two seconds. Each wave has one enemy
  // more than the previous one
  if (timer_.getSeconds() - kTimeChange >= kEpsilon) {
    if (number_of_particles_ < kMaxNumberOfEnemies) {
      number_of_particles_ += 1;
    }  // Increasing number of enemies every wave by 1

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
  const cinder::vec2 center = app::getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  PrintText("You have " + std::to_string(engine_->GetLives()) + " lives", color,
            size, vec2 (app::getWindowWidth() - global::kScalingFactor * 2,
                       static_cast<float>
                                                  (app::getWindowHeight
                                                   ()) -
                                             global::kScalingFactor));

  if (max_score_check_) {
        PrintText("You have finished your airballs!", color, size,
        vec2(app::getWindowWidth()/2, static_cast<float>(app::getWindowHeight
                                                                 ()) -
                                             global::kScalingFactor));
  }
  if (engine_->GetIsGameOver()) {
    size_t row = 0;
    PrintText("Game Over :(", color, size, center);
    PrintText("Your time was " + std::to_string((game_timer.getSeconds())) +
              " seconds",
              color, size, ivec2(app::getWindowCenter().x,
                                 app::getWindowCenter().y +
                                 + global::kScalingFactor));
    PrintText("Your score was " + std::to_string(engine_->GetGameScore()),
              color, size, ivec2(app::getWindowCenter().x,
                                 app::getWindowCenter().y +
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
  printf("No of bullets %u \n ", static_cast<int>(bullet_controller_
                                                      .GetBullets().size()));
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
  void MyApp::PlayBackGroundMusic() {
    auto source_file = cinder::audio::load
        (cinder::app::loadAsset("music.mp3"));
    background_audio_file = cinder::audio::Voice::create(source_file);
    background_audio_file->start();
  }
template <typename C>
void MyApp::PrintText(const std::string& text, const C& color, const
                         cinder::ivec2&size, const cinder::vec2& loc) {
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
}
}  // namespace myapp
