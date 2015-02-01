#ifndef RT_SPHERE_HPP
#define RT_SPHERE_HPP
#include "RT_Vec3.hpp"
#include "Ray.hpp"
#include "RT_Object.hpp"

class RT_Sphere : public RT_Object
{
    private:
        RT_Vec3 m_Center;
        double m_Radius;
    public:
        RT_Sphere();
        RT_Sphere(const RT_Vec3&, double);
        void setCenter(const RT_Vec3&);
        void setRadius(double);
        RT_Vec3 getCenter() const;
        double getRadius() const;
        INTERSECTION_TYPE isIntersected(const Ray&, double&);
        RT_Vec3 getNormal(const RT_Vec3&) const;
};

#endif

