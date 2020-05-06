#include <Box2D/Common/b2Math.h>

namespace mylibrary {

class Player {
 public:
  Player(b2Vec2 location) : loc(location) {}

  void SetLoc(b2Vec2 set_loc) { loc = set_loc; }
  b2Vec2 GetLoc() const { return loc; }

 private:
  b2Vec2 loc;
};

}  // namespace mylibrary
