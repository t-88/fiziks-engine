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
};

// Functions
std::string get_uuid();

#endif // Math_h