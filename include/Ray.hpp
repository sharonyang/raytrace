#ifndef RAY_HPP
#define RAY_HPP
#include "RT_Vec3.hpp"

class Ray
{
    private:
        RT_Vec3 origin;
        RT_Vec3 direction;
    public:
        Ray();
        Ray(const RT_Vec3&,const RT_Vec3&);
        void set_origin(const RT_Vec3&);
        void set_direction(const RT_Vec3&);
        RT_Vec3 get_origin() const;
        RT_Vec3 get_direction() const;
        RT_Vec3 get_point(double) const;
};

#endif
