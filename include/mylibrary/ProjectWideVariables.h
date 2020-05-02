#pragma once
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "../../apps/my_app.h"
#include "CoordinateConversions.h"
#include "EnemyController.h"
#include "cinder/app/AppBase.h"

namespace global {
const float kScalingFactor = 50;
const cinder::vec2 kBoxDimensions = cinder::vec2(25, 25);
}