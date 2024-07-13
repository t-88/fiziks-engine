#ifndef Math_h
#define Math_h


#include <string>
#include <random>



// Classes
// Vec2
class Vec2 {
public:
    float x , y; 
    ~Vec2();
    Vec2();
    Vec2(float x, float y);
    Vec2 operator *(float other) { return Vec2(x * other,y * other); }
    void operator +=(Vec2 other) { x += other.x; y += other.y; }
};

// Functions
std::string get_uuid();

#endif // Math_h