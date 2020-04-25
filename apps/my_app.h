// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_
#include "my_app.h"
#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
namespace myapp {
using namespace cinder::app;
class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup();
  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseMove(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void keyDown(KeyEvent event);
  void update();
  void draw();

  void DrawPlayer();

 private:
  float width_;
  float height_;
  bool is_mouse_pressed_;
  cinder::ivec2 mouse_position_;
  cinder::Timer timer_;
  cinder:: ivec2 mouse_velocity_;
  const int kTimeChange = 2;
  const double kDoubleEqualityChecker = 0.001;
  int number_of_particles_ = 5;
  void DrawBackground();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
