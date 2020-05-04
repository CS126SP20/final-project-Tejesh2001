// Copyright (c) 2020 [Tejesh Bhaumik]. All rights reserved.

#include "firebending_trials.h"

#include <cinder/audio/Voice.h>

#include <mylibrary/WorldCreator.hpp>
namespace trials {
using cinder::ivec2;
using cinder::vec2;
using cinder::app::KeyEvent;
cinder::audio::VoiceRef background_audio_file;
MyApp::MyApp() {
  b2Vec2 gravity(0, 100.0f);
  world_ = new b2World(gravity);
  player_ =
      new Player({ci::app::getWindowCenter().x, ci::app::getWindowCenter().y});
  engine_ = new Engine(*player_);
  mute_ = false;
  game_start_ = false;
  character_string = "avatar.gif";
}

void MyApp::setup() {
  if (!game_start_) {
    return;
  }
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
  LoadBackGroundMusic();
}
int c = 0;
void MyApp::update() {
  if (game_timer.isStopped()) {
    return;
  }
  //There is a wave of enemies every two seconds. Each wave has one enemy
  // more than the previous one

  if (timer_.getSeconds() - kTimeChange >= kEpsilon) {
    int number_of_enemies_ = randInt(kMinNumberOfEnemies, kMaxNumberOfEnemies);
    enemy_controller_.AddEnemies(number_of_enemies_);
    timer_.start(0.0);
  }  // Increasing number of enemies every wave by 1

  // Move physics world
  engine_->Step(*world_, enemy_controller_,
                                    bullet_controller_.GetBullets());
  bullet_controller_.update();
  enemy_controller_.update();

}

void MyApp::draw() {
  cinder::gl::clear(cinder::Color(0, 0, 0));
  cinder::gl::enableAlphaBlending();
  const cinder::vec2 center = ci::app::getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  ci::Color color = ci::Color::white();
  if (!game_start_) {
    DrawMenuScreen();
    return;
  }
  DrawBackground("background.png");
  DrawPlayer();
  bullet_controller_.draw();
  enemy_controller_.draw();
  PrintText("You have " + std::to_string(engine_->GetLives()) + " lives", color,
            size,
            vec2(ci::app::getWindowWidth() - global::kScalingFactor * 2,
                 static_cast<float>(ci::app::getWindowHeight()) -
                     global::kScalingFactor));

  if (bullet_controller_.GetBullets().size() > kMaxNumberOfBullets) {
    PrintText("You have finished your airballs!", color, size,
              vec2(ci::app::getWindowWidth() / 2,
                   static_cast<float>(ci::app::getWindowHeight()) -
                       global::kScalingFactor));
  }
  if (engine_->GetIsGameOver()) {
    DrawGameOver(center, color, size);
    game_timer.stop();
  }
}
void MyApp::DrawMenuScreen() {
  const cinder::vec2 center = ci::app::getWindowCenter();
  const cinder::ivec2 size = {200, 500};
  DrawBackground("world.jpg");
  PrintText("Choose your character first. \n Press 1 for Aang, 2 for Katara",
            ci::Color::black(), size, center);
  PrintText("Press the spacebar to start", ci::Color::black(), size,
            ivec2(app::getWindowCenter().x,
                  app::getWindowCenter().y + +global::kScalingFactor));
  gl::Texture2dRef texture = LoadPlayer("aang1.png");
  gl::draw(texture,
           Rectf(center.x - kMenuSpriteIndexLarge * global::kScalingFactor,
                 center.y + global::kScalingFactor,
                 center.x - kMenuSpriteIndexSmall * global::kScalingFactor,
                 center.y + kMenuSpriteHeight * global::kScalingFactor));
  texture = LoadPlayer("katara.png");
  gl::draw(texture,
           Rectf(center.x + kMenuSpriteIndexSmall * global::kScalingFactor,
                 center.y + global::kScalingFactor,
                 center.x + kMenuSpriteIndexLarge * global::kScalingFactor,
                 center.y + kMenuSpriteHeight * global::kScalingFactor));
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
      if (bullet_controller_.GetBullets().size() <= kMaxNumberOfBullets) {
        AddBullet();
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
      game_start_ = true;
      setup();
      break;
    }
    case KeyEvent::KEY_m: {
      if (!mute_) {
        PauseBackGroundMusic();
        mute_ = true;
      } else {
        mute_ = false;
        PlayBackGroundMusic();
      }
      break;
    }
    case KeyEvent::KEY_1: {
      character_string = "avatar.gif";
      break;
    }
    case KeyEvent::KEY_2: {
      character_string = "katara.png";
      break;
    }
  }
}
void MyApp::PauseBackGroundMusic() const { background_audio_file->pause(); }

void MyApp::mouseDown(cinder::app::MouseEvent /*event*/) {
  if (bullet_controller_.GetBullets().size() <= kMaxNumberOfBullets) {
    AddBullet();
  }
}
void MyApp::AddBullet() {
  const b2Vec2 loc = engine_->GetPlayer().GetLoc();
  bullet_controller_.addBullet(loc);
}
cinder::gl::Texture2dRef MyApp::LoadPlayer(std::string relative_path) {
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(cinder::app::loadAsset(relative_path)));
  return texture;
}

void MyApp::DrawPlayer() {
  const b2Vec2 loc = engine_->GetPlayer().GetLoc();
  cinder::gl::Texture2dRef texture;
  texture = LoadPlayer(character_string);
  cinder::gl::draw(texture,
                   ci::Rectf(loc.x, loc.y, loc.x + 2 * global::kScalingFactor,
                             loc.y + 2 * global::kScalingFactor));
}

void MyApp::DrawBackground(const std::string& relative_path) {
  cinder::fs::path path = cinder::fs::path(relative_path);
  cinder::gl::Texture2dRef texture =
      cinder::gl::Texture2d::create(loadImage(cinder::app::loadAsset(path)));
  cinder::gl::draw(texture, ci::Rectf(getWindowBounds()));
}
void MyApp::LoadBackGroundMusic() {
  auto source_file = cinder::audio::load(cinder::app::loadAsset("mus.mp3"));
  background_audio_file = cinder::audio::Voice::create(source_file);
  PlayBackGroundMusic();
}
void MyApp::PlayBackGroundMusic() const { background_audio_file->start(); }
template <typename C>
void MyApp::PrintText(const std::string& text, const C& color,
                      const cinder::ivec2& size, const cinder::vec2& loc) {
  auto box = ci::TextBox()
                 .alignment(ci::TextBox::CENTER)
                 .font(cinder::Font("Ariel", 30))
                 .size(size)
                 .color(color)
                 .backgroundColor(ci::ColorA(1, 1, 1, 0))
                 .text(text);
  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}
void MyApp::DrawGameOver(const ci::vec2 center, const ci::Color color,
                         const ci::ivec2 size) {
  DrawBackground("start.jpg");
  PrintText("Game Over :(", color, size, center);
  PrintText("Your time was " +
                std::to_string(static_cast<int>(game_timer.getSeconds())) +
                " seconds",
            color, size,
            ivec2(ci::app::getWindowCenter().x,
                  ci::app::getWindowCenter().y + +global::kScalingFactor));
  PrintText("Your score was " + std::to_string(engine_->GetGameScore()), color,
            size,
            ivec2(ci::app::getWindowCenter().x,
                  ci::app::getWindowCenter().y + 2 * global::kScalingFactor));
}
}  // namespace trials
