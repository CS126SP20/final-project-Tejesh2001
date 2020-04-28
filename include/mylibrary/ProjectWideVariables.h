#pragma once
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "../../apps/my_app.h"
#include "CoordinateConversions.h"
#include "EnemyController.h"
#include "cinder/app/AppBase.h"

namespace global {
const int kPlayerHeight = 15;
const int kPlayerWidth = 15;
const float kScalingFactor = 50;
const cinder::vec2 kBoxDimensions = cinder::vec2(30, 30);
//TODO NAMING CONVENTION
static int color_change = 0;
}