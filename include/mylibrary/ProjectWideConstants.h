#pragma once
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "../../apps/firebending_trials.h"
#include "CoordinateConversions.h"
#include "EnemyController.h"
#include "cinder/app/AppBase.h"

namespace global {
const float kScalingFactor = 50;
const cinder::vec2 kBoxDimensions = cinder::vec2(25, 25);
const int kBoundsOfWindow = 800;
const float kLeftMostIndex = 0;
const float kLowerMostIndex = 0;
const float kFriction = 0.2f;
const float kDensity = 0.3f;
const float kRestitution = 10.0f;
}  // namespace global