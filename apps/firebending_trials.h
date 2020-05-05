// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_
#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <mylibrary/ProjectWideConstants.h>

#include <mylibrary/BulletController.hpp>

#include "firebending_trials.h"
#include "mylibrary/direction.h"
#include "mylibrary/engine.h"
namespace trials {
using namespace cinder::app;
class MyApp : public cinder::app::App {
 public:
  /**Constructor initialises the data variables**/
  MyApp();

  /**Sets up the game**/
  void setup();

  /**Checks if the mouse is pressed**/
  void mouseDown(MouseEvent event);

  /**Checks which key is pressed and performs the respective action**/
  void keyDown(KeyEvent event);

  /**Updates the game state**/
  void update();

  /**Draws the game**/
  void draw();

 private:
  /**Height of the spirtes in the Box2D world**/
  const int kMenuSpriteHeight = 5;

  /**Bounds of sprite indexes in the Box2D world**/
  const int kMenuSpriteIndexLarge = 7;
  const int kMenuSpriteIndexSmall = 3;

  /**Stores the image of the character chosen**/
  std::string character_string;

  /** Timer to regulate enemy waves**/
  cinder::Timer timer_;

  /**Each wave of enemies comes after 2 seconds**/
  const int kTimeChange = 2;

  /**Helps for checking with double**/
  const double kEpsilon = 0.001;

  /**Checks if volume is muted**/
  bool mute_;

  /**Keeps track of  game time**/
  cinder::Timer game_timer;

  /**The maximum number of bullets on screen**/
  const int kMaxNumberOfBullets = 2;

  /**The starting amount of enemies**/
  int kMinNumberOfEnemies = 5;

  /**Checks if game has started**/
  bool game_start_;

  /**The Box2D world**/
  b2World* world_;

  /**The player**/
  Player* player_;

  /**The engine pointer**/
  Engine* engine_;

  /**Maximum number of enemies in a wave**/
  const int kMaxNumberOfEnemies = 14;

  /** The enemy controller object**/
  EnemyController enemy_controller_;

  /**The bullet controller object**/
  BulletController bullet_controller_;

  /**Player 1 string path**/
  const char* const kCharacter1Name = "aang1.png";

  /**Player 2 string path**/
  const char* const kCharacter2Name = "katara.png";

  /**Draws background**/
  void DrawBackground(const std::string&);

  /**Prints text onto the screen**/
  template <typename C>
  void PrintText(const std::string& text, const C& color,
                 const glm::ivec2& size, const glm::vec2& loc,
                 ci::ColorA box_color);

  /**Adds bullet to bullet vector and creates the body**/
  void AddBullet();

  /**Loads backgroundMusic to be played**/
  void LoadBackGroundMusic();

  /**Plays background music**/
  void PlayBackGroundMusic() const;

  /**Pauses background music**/
  void PauseBackGroundMusic() const;

  /**Loads Player path**/
  cinder::gl::Texture2dRef LoadPlayer(std::string relative_path);

  /**Draws player**/
  void DrawPlayer();

  /**Draws menu screen**/
  void DrawMenuScreen();

  /**Draws game over**/
  void DrawGameOver(const ci::vec2 center, const ci::Color color,
                    const ci::ivec2 size);

  /**Resets the game for restart**/
  void Reset();

  /**Checks if the sprite on the menu is selected**/
  void CheckIfMenuSpriteIsSelected(const MouseEvent& event);
};

}  // namespace trials

#endif  // FINALPROJECT_APPS_MYAPP_H_
