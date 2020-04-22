#include "my_app.h"

#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>
#include "CoordinateConversions.h"
#include "ParticleController.h"
#include "cinder/app/AppBase.h"


class Player {
 public:
  void SetLoc (const vec2& set_loc) {
    loc = set_loc;
  }
  vec2 GetLocation() const { return loc;}
  void draw();
  void MovePlayer(const vec2& vec);
 private:
  vec2 loc;
  bool draw_first = true;
};


