#include <array>
#include <limits>
#include <math.h>

#include "CollisionDetection.hpp"
#include "Rect.hpp"
#include "Math.hpp"

namespace CollisionDetection
{
    static std::pair<float,float> project_rect_to_line(std::array<Vec2,4>& points, Vec2 line) {
        //TODO: make it work for any polygon, change the point limit to whatever
        std::pair<float,float> bounds;
        bounds.first  =  std::numeric_limits<float>::max();
        bounds.second = std::numeric_limits<float>::min();
        for(int i = 0; i < 4; i++) {
            float proj = points[i] * line;
            if(bounds.first > proj) bounds.first = proj;
            if(bounds.second < proj) bounds.second = proj;
        }
        return bounds;
    }

    bool SAT(Rect a, Rect b, Vec2& MTV) {
        std::array<Vec2,4> a_points = a.getPoints();
        std::array<Vec2,4> b_points = b.getPoints();

        Vec2 normal;
        float min_overlap = std::numeric_limits<float>::max();
        std::pair<float,float> bounds_a , bounds_b;

        for(int i = 0; i < 4; i++) {
            normal = (a_points[i] - a_points[(i + 1) % 4]).normal().normalize();
            bounds_a = project_rect_to_line(a_points,normal);
            bounds_b = project_rect_to_line(b_points,normal);
            // intersection check
            if(!(bounds_a.second > bounds_b.first && bounds_b.second > bounds_a.first)) {
                return false;
            } else {
                float overlap = std::min(bounds_a.second - bounds_b.first, bounds_b.second - bounds_a.first);
                if(min_overlap > overlap) {
                    MTV = normal;
                    min_overlap = overlap;
                }
            }
        }


        for(int i = 0; i < 4; i++) {
            normal = (b_points[i] - b_points[(i + 1) % 4]).normal().normalize();
            bounds_a = project_rect_to_line(a_points,normal);
            bounds_b = project_rect_to_line(b_points,normal);
            // intersection check
            if(!(bounds_a.second > bounds_b.first && bounds_b.second > bounds_a.first)) {
                return false;
            } else {
                float overlap = std::min(bounds_a.second - bounds_b.first, bounds_b.second - bounds_a.first);
                if(min_overlap > overlap) {
                    MTV = normal;
                    min_overlap = overlap;
                }
            }
        }


        MTV *= min_overlap;

        // from a to b 
        Vec2 diff = b.pos - a.pos;
        if(diff * MTV < 0) {
            MTV *= -1;
        }        

        return true;
    }    
} 
