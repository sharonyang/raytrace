#include "include/Ray.hpp"
#include "include/RT_Vec3.hpp"

Ray::Ray() {}
Ray::Ray(const RT_Vec3& ori, const RT_Vec3& dir) : origin(ori), direction(dir)
{
  direction.normalize();
}

void Ray::set_origin(const RT_Vec3& ori)
{
    origin = ori;
}

void Ray::set_direction(const RT_Vec3& dir)
{
    direction = dir;
    direction.normalize();
}

RT_Vec3 Ray::get_origin() const
{
    return origin;
}

RT_Vec3 Ray::get_direction() const
{
    return direction;
}

RT_Vec3 Ray::get_point(double f) const
{
    if (direction.length() == 0)
    {
        return direction;
    }
    return origin+direction*f;
}
