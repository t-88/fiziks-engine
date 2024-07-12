#include "Body.hpp"


Body::~Body() {}
Body::Body(Vec2 pos = Vec2(0,0), float mass = 0) : pos(pos),  mass(mass),invMass(mass == 0 ? 0 : 1.f / mass), uuid(get_uuid()) { 

}
