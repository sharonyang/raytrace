#include "include/RT_Floor.hpp"
#include <iostream>

RT_Floor::RT_Floor() {}
RT_Floor::RT_Floor(const RT_Vec3& normal, const RT_Vec3& point) :
    m_Normal(normal), m_Point(point) {}

void RT_Floor::setNormal(const RT_Vec3& normal)
{
    m_Normal = normal;
}

void RT_Floor::setPoint(const RT_Vec3& point)
{
    m_Point = point;
}

RT_Vec3 RT_Floor::getNormal() const
{
    return m_Normal;
}

RT_Vec3 RT_Floor::getPoint() const
{
    return m_Point;
}

RT_Vec3 RT_Floor::getNormal(const RT_Vec3& v) const
{
    return m_Normal;
}

INTERSECTION_TYPE RT_Floor::isIntersected(const Ray& ray, double& point)
{
    double tmp1 = m_Point * m_Normal - m_Normal * ray.get_origin();
    double tmp2 = m_Normal * ray.get_direction();
    double t = tmp1 / tmp2;
    if (t < 0)
        return MISS;
    if (point > t)
    {
        point = t;
        return INTERSECTED_OUT;
    }
    return MISS;
}
