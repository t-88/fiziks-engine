#include "Body.hpp"


Body::~Body() {}
Body::Body(Vec2 pos = Vec2(0,0), float mass = 0,float rotation = 0,bool isStatic = false) : pos(pos),  mass(mass),invMass(mass == 0 ? 0 : 1.f / mass), 
                                                                         isStatic(isStatic), uuid(get_uuid()),
                                                                         rotation(rotation) {

  }

void Body::applyForce(Vec2 f) { force += f * FORCE_SCALE; }
void Body::applyTorque(float t) { torque += t * TORQUE_SCALE; }
