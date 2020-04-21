#pragma once
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

#include "CoordinateConversions.h"
#include "ParticleController.h"
#include "cinder/app/AppBase.h"
#include "my_app.h"

namespace global {
const float kBoxXMin = 10.0f;
const float kBoxXMax = 20.0f;
const float kBoxYMin = 10.0f;
const float kBoxYMax = 20.0f;
//TODO NAMING CONVENTION
static int color_change = 0;
}