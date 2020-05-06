// Copyright (c) 2020 [Tejesh Bhaumik]. All rights reserved.

#include "firebending_trials.h"
#include <mylibrary/WorldCreator.hpp>
namespace trials {
using cinder::ivec2;
using cinder::vec2;
using cinder::app::KeyEvent;
MyApp::MyApp() {
  b2Vec2 gravity(0, 100.0f);
  world_ = new b2World(gravity);
  // Assigns player pointer
  player_ = new mylibrary::Player(
      {ci::app::getWindowCenter().x, ci::app::getWindowCenter().y});
  // Assigns engine pointer
  engine_ = new mylibrary::Engine(*player_);
  mute_ = false;
  game_start_ = false;
  character_string_ = kCharacter1Name;
}

void MyApp::setup() {
  if (!game_start_) {
    return;
  }
  mylibrary::WorldCreator world_creator;
  // The functions for creating walls for separated for generalization
  world_creator.CreateCeiling(*world_);
  world_creator.CreateLeftWall(*world_);
  world_creator.CreateRightWall(*world_);
  // pass *world to objects
  timer_.start(0);
  game_timer.start(0);
  enemy_controller_.setup(*world_);
  bullet_controller_.setup(*world_);
  LoadBackGroundMusic();
}
void MyApp::update() {
  if (game_timer.isStopped()) {
    // If you restart the game, the enemies need to be cleared
    enemy_controller_.GetEnemies().clear();
    return;
  }
  // There is a wave of enemies every two seconds. Each wave has one enemy
  // more than the previous one

  if (timer_.getSeconds() - kTimeChange >= kEpsilon) {
    int number_of_enemies_ =
        ci::randInt(kMinNumberOfEnemies, kMaxNumberOfEnemies);
    enemy_controller_.AddEnemies(number_of_enemies_);
    timer_.start(0.0);
  }  // Randomising number of enemies every wave

  // Move physics world
  engine_->Step(*world_, enemy_controller_, bullet_controller_.GetBullets());
  bullet_controller_.update();
  enemy_controller_.update();
}

void MyApp::draw() {
  // Clears the screen with a white color
  ci::gl::clear(ci::Color(0, 0, 0));
  ci::gl::enableAlphaBlending();
  const ci::vec2 center = ci::app::getWindowCenter();
  // Size of font
  const ci::ivec2 size = {500, 45};
  // Color of font
  ci::Color color = ci::Color::white();
  /**Draws menu screen**/
  if (!game_start_) {
    DrawMenuScreen();
    return;
  }
  /**Draws gameplay **/
  DrawBackground("background.png");
  DrawPlayer();
  bullet_controller_.draw();
  enemy_controller_.draw();
  // This contains the heart unicode
  const std::string heart_unicode = u8"\u2764";
  std::string lives;
  for (int i = 0; i < engine_->GetLives(); i++) {
    lives.append(heart_unicode);
    lives.append(" ");
  }
  // Enables alpha blending by making the last parameter 0
  ci::ColorA box_transparent_color = ci::ColorA(1, 1, 1, 0);
  PrintText("Lives " + lives, color, size,
            vec2(ci::app::getWindowWidth() - global::kScalingFactor * 2,
                 static_cast<float>(ci::app::getWindowHeight()) -
                     global::kScalingFactor),
            box_transparent_color);

  if (bullet_controller_.GetBullets().size() > kMaxNumberOfBullets) {
    PrintText("You have finished your airballs!", color, size,
              vec2(ci::app::getWindowWidth() / 2,
                   static_cast<float>(ci::app::getWindowHeight()) -
                       global::kScalingFactor),
              box_transparent_color);
  }
  /**Draws game over**/
  if (engine_->GetIsGameOver()) {
    DrawGameOver(center, color, size);
    game_timer.stop();
  }
}
void MyApp::DrawMenuScreen() {
  const ci::vec2 center = ci::app::getWindowCenter();
  // Sets the size of the writing
  const ci::ivec2 size = {500, 45};
  // The 1 enables alpha blending
  const ci::ColorA box_opaque_color = ci::ColorA(1, 1, 1, 1);
  DrawBackground("world.jpg");
  PrintText("Click on the character you want", ci::Color::black(), size, center,
            box_opaque_color);
  PrintText("Press the spacebar to start", ci::Color::black(), size,
            ivec2(ci::app::getWindowCenter().x,
                  ci::app::getWindowCenter().y + global::kScalingFactor),
            box_opaque_color);
  ci::gl::Texture2dRef texture = LoadPlayer(kCharacter1Name);
  // Draws the menu sprites on the tiles present on the world map
  ci::gl::draw(
      texture,
      ci::Rectf(center.x - kMenuSpriteIndexLarge * global::kScalingFactor,
                center.y + global::kScalingFactor,
                center.x - kMenuSpriteIndexSmall * global::kScalingFactor,
                center.y + kMenuSpriteHeight * global::kScalingFactor));
  texture = LoadPlayer(kCharacter2Name);
  ci::gl::draw(
      texture,
      ci::Rectf(center.x + (kMenuSpriteIndexSmall)*global::kScalingFactor,
                center.y + global::kScalingFactor,
                center.x + (kMenuSpriteIndexLarge)*global::kScalingFactor,
                center.y + kMenuSpriteHeight * global::kScalingFactor));
}
void MyApp::keyDown(KeyEvent event) {
  // The first four cases are responsible for player movement
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
    // Fires bullets
    case KeyEvent::KEY_RETURN: {
      if (bullet_controller_.GetBullets().size() <= kMaxNumberOfBullets) {
        AddBullet();
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
      // Starts the game
      game_start_ = true;
      setup();
      break;
    }
    case KeyEvent::KEY_RSHIFT: {
      // Restarts the game
      game_start_ = true;
      Reset();
      setup();
      break;
    }
      // Mutes the music
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
  }
}
void MyApp::PauseBackGroundMusic() const { background_audio_file_->pause(); }

void MyApp::mouseDown(ci::app::MouseEvent event) {
  // Chooses the character which is clicked on
  if (!game_start_) {
    CheckIfMenuSpriteIsSelected(event);
  } else {
    // Shoots bullets
    if (bullet_controller_.GetBullets().size() <= kMaxNumberOfBullets) {
      AddBullet();
    }
  }
}
void MyApp::CheckIfMenuSpriteIsSelected(const MouseEvent& event) {
  // This checks if the mouse position when clicked matches with the position
  // at which the menu sprite is drawn
  float left_dimension_of_sprite =
      ci::app::getWindowCenter().x -
      kMenuSpriteIndexLarge * global::kScalingFactor;
  float right_dimension_of_sprite =
      ci::app::getWindowCenter().x -
      kMenuSpriteIndexSmall * global::kScalingFactor;

  // It goes through all the the rows that the sprite is drawn on
  for (float x = left_dimension_of_sprite; x <= right_dimension_of_sprite;
       x += global::kScalingFactor) {
    if ((int)(event.getPos().x / global::kScalingFactor) ==
        (int)(x / global::kScalingFactor)) {
      character_string_ = kCharacter1Name;
    }
  }
  left_dimension_of_sprite = ci::app::getWindowCenter().x +
                             (kMenuSpriteIndexSmall)*global::kScalingFactor;
  right_dimension_of_sprite = ci::app::getWindowCenter().x +
                              kMenuSpriteIndexLarge * global::kScalingFactor;
  for (float x = left_dimension_of_sprite; x <= right_dimension_of_sprite;
       x += global::kScalingFactor) {
    if ((int)(event.getPos().x / global::kScalingFactor) ==
        (int)(x / global::kScalingFactor)) {
      character_string_ = kCharacter2Name;
    }
  }
}
void MyApp::AddBullet() {
  // Adds bullet to vector at position where player has drawn
  const b2Vec2 loc = engine_->GetPlayer().GetLoc();
  bullet_controller_.addBullet(loc);
}
ci::gl::Texture2dRef MyApp::LoadPlayer(std::string relative_path) {
  // Loads the player path from the string
  ci::gl::Texture2dRef texture =
      ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(relative_path)));
  return texture;
}

void MyApp::DrawPlayer() {
  const b2Vec2 loc = engine_->GetPlayer().GetLoc();
  ci::gl::Texture2dRef texture;
  texture = LoadPlayer(character_string_);
  ci::gl::draw(texture,
               ci::Rectf(loc.x, loc.y, loc.x + 2 * global::kScalingFactor,
                         loc.y + 2 * global::kScalingFactor));
}

void MyApp::DrawBackground(const std::string& relative_path) {
  // Loads path of background
  ci::fs::path path = ci::fs::path(relative_path);
  ci::gl::Texture2dRef texture =
      ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(path)));
  ci::gl::draw(texture, ci::Rectf(getWindowBounds()));
}
void MyApp::LoadBackGroundMusic() {
  auto source_file = ci::audio::load(ci::app::loadAsset("mus.mp3"));
  background_audio_file_ = ci::audio::Voice::create(source_file);
  PlayBackGroundMusic();
}
void MyApp::PlayBackGroundMusic() const { background_audio_file_->start(); }
template <typename C>
void MyApp::PrintText(const std::string& text, const C& color,
                      const ci::ivec2& size, const ci::vec2& loc,
                      const ci::ColorA box_color) {
  auto box = ci::TextBox()
                 .alignment(ci::TextBox::CENTER)
                 .font(ci::Font("Garamond", 45))
                 .size(size)
                 .color(color)
                 .backgroundColor(box_color)
                 .text(text);
  const auto box_size = box.getSize();
  const ci::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = ci::gl::Texture::create(surface);
  ci::gl::draw(texture, locp);
}
void MyApp::DrawGameOver(const ci::vec2 center, const ci::Color color,
                         const ci::ivec2 size) {
  DrawBackground("start.jpg");
  ci::ColorA box_transparent_color = ci::ColorA(1, 1, 1, 0);
  PrintText("Game Over :(", color, size, center, box_transparent_color);
  PrintText("Your time was " +
                std::to_string(static_cast<int>(game_timer.getSeconds())) +
                " seconds",
            color, size,
            ivec2(ci::app::getWindowCenter().x,
                  ci::app::getWindowCenter().y + +global::kScalingFactor),
            box_transparent_color);
  // The magic numbers are present for printing each line below each other
  PrintText("Your score was " + std::to_string(engine_->GetGameScore()), color,
            size,
            ivec2(ci::app::getWindowCenter().x,
                  ci::app::getWindowCenter().y + 2 * global::kScalingFactor),
            box_transparent_color);

  PrintText("Press shift to play again ", color, size,
            ivec2(ci::app::getWindowCenter().x,
                  ci::app::getWindowCenter().y + 3 * global::kScalingFactor),
            box_transparent_color);
}

void MyApp::Reset() {
  // Used to restart the game with same parameters as before
  player_ = new mylibrary::Player(
      {ci::app::getWindowCenter().x, ci::app::getWindowCenter().y});
  engine_ = new mylibrary::Engine(*player_);
  mute_ = false;
  game_start_ = false;
  character_string_ = kCharacter1Name;
}

}  // namespace trials
