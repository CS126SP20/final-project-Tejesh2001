#pragma once
#include <cinder/gl/gl.h>
#include "CoordinateConversions.h"
#include "cinder/Vector.h"
#include "cinder/app/AppBase.h"
//Code derived from https://box2d.org/posts/2011/12/pixels/
using namespace ci;
namespace conversions {

/**Conversion factor to convert onscreen coordinates to Box2D**/
static float GetScaling() {
  const static float kScaling = 50.0f;
  return kScaling;
}
/**Converts Box2D coordinates to onscreen coordinates**/
static vec2 ToScreen(b2Vec2 fin) { return vec2(fin.x, fin.y) * GetScaling(); }

/**Converts onscreen coordinates to Box2D coordinates**/
static float ToBox2DCoordinates(float fin) { return fin / GetScaling(); }

/**Converts radians to degrees**/
static float RadiansToDegrees(float rad) { return float(rad * 180.0f / M_PI); }
};
