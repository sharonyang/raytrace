#include "include/RT_Sphere.hpp"
#include <cmath>


RT_Sphere::RT_Sphere() : m_Radius(0.0f) {};
RT_Sphere::RT_Sphere(const RT_Vec3& c, double r) : m_Center(c), \
    m_Radius(r) {};

void RT_Sphere::setCenter(const RT_Vec3& c)
{
    m_Center = c;
}

void RT_Sphere::setRadius(double f)
{
    m_Radius = f;
}

RT_Vec3 RT_Sphere::getCenter() const
{
    return m_Center;
}

double RT_Sphere::getRadius() const
{
    return m_Radius;
}

INTERSECTION_TYPE RT_Sphere::isIntersected(const Ray& ray, double& dis)
{
    double A = ray.get_direction() * ray.get_direction();
    double B = ray.get_direction() * (ray.get_origin()-this->m_Center) * 2.0f;
    double C = (ray.get_origin()-this->m_Center) * \
        (ray.get_origin() - this->m_Center) - this->m_Radius * \
        this->m_Radius;
    double deta = B * B - 4 * A * C;
    INTERSECTION_TYPE result = MISS;
    if (deta < 0)
    {
        return MISS;
    }
    deta = sqrt(deta);
    double x1 = (-B - deta) / 2.0f;
    double x2 = (-B + deta) / 2.0f;
    if (x2 > 0)
    {
        if (x1 < 0)
        {
            if (x2 < dis)
            {
                dis = x2;
                result = INTERSECTED_IN;
            }
        }
        else
        {
            if (x1 < dis)
            {
                dis = x1;
                result = INTERSECTED_OUT;
            }
        }
    }
    return result;
}

RT_Vec3 RT_Sphere::getNormal(const RT_Vec3& v) const
{
    return v-m_Center;
}
