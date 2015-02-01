#ifndef RT_Floor_HPP
#define RT_Floor_HPP
#include "RT_Vec3.hpp"
#include "Ray.hpp"
#include "RT_Object.hpp"

class RT_Floor : public RT_Object
{
    private:
        RT_Vec3 m_Normal;
        RT_Vec3 m_Point;
    public:
        RT_Floor();
        RT_Floor(const RT_Vec3& normal, const RT_Vec3& point);
        void setNormal(const RT_Vec3&);
        void setPoint(const RT_Vec3&);
        RT_Vec3 getNormal() const;
        RT_Vec3 getPoint() const;
        RT_Vec3 getNormal(const RT_Vec3&) const;
        INTERSECTION_TYPE isIntersected(const Ray&, double&);
};

#endif

