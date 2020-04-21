#pragma once
#include <cinder/gl/gl.h>

#include "Box2D/Box2D.h"
#include "CoordinateConversions.h"
#include "ParticleController.h"
#include "cinder/Vector.h"
#include "cinder/app/AppBase.h"
#include "my_app.h"
//Code derived from https://box2d.org/posts/2011/12/pixels/
using namespace ci;
namespace conversions {
			
static float GetScaling() {
  static float scaling = 50.0f;
  return scaling;
}
			
static vec2 ToScreen( b2Vec2 fin )
{
  return vec2(fin.x, fin.y) * GetScaling();
}
static float ToBox2DCoordinates( float fin )
{
  return fin / GetScaling();
}
			
static float RadiansToDegrees( float rad )
{
  return rad * 180.0f/M_PI;
}
};
