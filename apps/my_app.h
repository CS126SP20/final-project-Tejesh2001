// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>

#include "BoxController.hpp"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  b2World* my_world;
  BoxController box_controller;
  cinder::vec2  mouse_location;
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;
  void mouseMove(cinder::app::MouseEvent) override;
  void mouseDrag(cinder::app::MouseEvent event ) override;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
