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

    bool SAT(Rect a, Rect b, Vec2& MTV,float& overlap) {
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


        overlap = min_overlap;
        // from a to b 
        Vec2 diff = b.pos - a.pos;
        if(diff * MTV < 0) {
            MTV *= -1;
        }        

        return true;
    }    


    static Vec2 point_line_closest_point(Vec2 b, Vec2 a, Vec2 c, float& distance) {
        Vec2 ab = (b - a);
        Vec2 ac = (c - a);
        float proj = ac * ab / (ab * ab);
        Vec2 close_point;
        if(proj < 0) {
            close_point = a;
        } else if (proj > 1) {
            close_point = b;
        } else {
            close_point = a + ab * proj;
        }
        distance = (c - close_point).length();
        return close_point;
    }

    static bool equal_floats(float a , float b) {
        #define EPSILON 0.001
        return std::abs(a - b) <= EPSILON;
    }



    std::pair<int,std::array<Vec2,2>> getContactPoints(Rect a, Rect b) {
        std::array<Vec2,4> a_points = a.getPoints();
        std::array<Vec2,4> b_points = b.getPoints();

        std::pair<int,std::array<Vec2,2>> contact_points;
        contact_points.first = 0;
        float min_distance = std::numeric_limits<float>::max();

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                float distance;
                Vec2 closest_point = point_line_closest_point(b_points[j],b_points[(j + 1) % 4],a_points[i],distance);
                if(equal_floats(min_distance,distance)) {
                    contact_points.first = 2;
                    contact_points.second[1] = closest_point;
                }
                else if(min_distance >= distance) {
                    min_distance = distance;
                    contact_points.first = 1;
                    contact_points.second[0] = closest_point;
                }
            }
        }

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                float distance;
                Vec2 closest_point = point_line_closest_point(a_points[j],a_points[(j + 1) % 4],b_points[i],distance);
                if(equal_floats(min_distance,distance)) {
                    contact_points.first = 2;
                    contact_points.second[1] = closest_point;
                }
                else if(min_distance >= distance) {
                    min_distance = distance;
                    contact_points.first = 1;
                    contact_points.second[0] = closest_point;
                }
            }
        }


        return contact_points;
    }

} 
