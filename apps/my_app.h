// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_
#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <mylibrary/ProjectWideConstants.h>

#include <mylibrary/BulletController.hpp>

#include "my_app.h"
#include "mylibrary/direction.h"
#include "mylibrary/engine.h"
namespace myapp {
using namespace cinder::app;
class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup();
  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void keyDown(KeyEvent event);
  void update();
  void draw();
  void DrawPlayer();

 private:
  bool is_mouse_pressed_;
  cinder::Timer timer_;
  const int kTimeChange = 2;
  const double kEpsilon = 0.001;
  bool mute_;
  cinder::Timer game_timer;
  bool max_score_check_;
  const int kMaxNumberOfBullets = 2;
  int number_of_particles_ = 5;
  bool game_start_;
  b2World* world_;
  Player* player_;
  Engine* engine_;
  static const int kMaxNumberOfEnemies = 12;
  EnemyController enemy_controller_;
  BulletController bullet_controller_;
  void DrawBackground(const std::string&);
  template <typename C>
  void PrintText(const std::string& text, const C& color,
                 const glm::ivec2& size, const glm::vec2& loc);
  void AddBullet();
  void LoadBackGroundMusic();
  void PlayBackGroundMusic() const;
  void PauseBackGroundMusic() const;
  auto LoadPlayer();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
