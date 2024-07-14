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
    float operator *(Vec2 other) { return x * other.x + y * other.y; }
    Vec2 operator +(Vec2 other) { return Vec2(x + other.x,y + other.y); }
    Vec2 operator -(Vec2 other) { return Vec2(x - other.x,y - other.y); }
    void operator +=(Vec2 other) { x += other.x; y += other.y; }
    void operator -=(Vec2 other) { x -= other.x; y -= other.y; }
    void operator *=(float other) { x *= other; y *= other; }
    Vec2& operator = (Vec2 other) { x = other.x; y= other.y; return *this; }
    Vec2 normal() { return Vec2(-y,x); }
    float distance(Vec2 other) {return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));}
    float length() {return std::sqrt(x * x + y  * y);}
    Vec2 normalize();
};

inline Vec2 operator *(float a,Vec2 b) { return Vec2(b.x * a,b.y * a); }
inline Vec2 operator *(Vec2 b,float a) { return Vec2(b.x * a,b.y * a); }
inline Vec2 operator /(float a,Vec2 b) { return Vec2(b.x / a,b.y / a); }
inline Vec2 operator /(Vec2 b,float a) { return Vec2(b.x / a,b.y / a); }


// Functions
std::string get_uuid();

#endif // Math_h