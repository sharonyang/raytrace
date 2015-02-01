#include <cmath>
#include <iostream>
#include "include/RT_Vec3.hpp"

RT_Vec3::RT_Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

RT_Vec3::RT_Vec3(const RT_Vec3& input_vec) : \
    x(input_vec.x), y(input_vec.y), z(input_vec.z) {}

RT_Vec3::RT_Vec3(double xx, double yy, double zz) : \
    x(xx), y(yy), z(zz) {}

double RT_Vec3::length() const
{
    return sqrt(x * x + y * y + z * z);
}

bool RT_Vec3::normalize()
{
    double len = this->length();
    if (len == 0)
        return false;
    x /= len;
    y /= len;
    z /= len;
    
    return true;
}

RT_Vec3 RT_Vec3::cross(const RT_Vec3& input_vec)
{
    RT_Vec3 result;
    result.x = y * input_vec.z - z * input_vec.y;
    result.y = z * input_vec.x - x * input_vec.z;
    result.z = x * input_vec.y - y * input_vec.x;
    return result;
}

RT_Vec3 RT_Vec3::operator=(const RT_Vec3& input_vec)
{
    x = input_vec.x;
    y = input_vec.y;
    z = input_vec.z;
    return *this;
}

RT_Vec3 RT_Vec3::operator=(double f)
{
    x = f;
    y = f;
    z = f;
    return *this;
}

RT_Vec3 RT_Vec3::operator+(const RT_Vec3& input_vec) const
{
    RT_Vec3 g1(x + input_vec.x, y + input_vec.y, z + input_vec.z);
    return g1;
}

RT_Vec3 RT_Vec3::operator+=(const RT_Vec3& input_vec)
{
    x += input_vec.x;
    y += input_vec.y;
    z += input_vec.z;
    return *this;
}

RT_Vec3 RT_Vec3::operator-(const RT_Vec3& input_vec) const
{
    RT_Vec3 g1(x-input_vec.x, y-input_vec.y, z-input_vec.z);
    return g1;
}

RT_Vec3 RT_Vec3::operator-=(const RT_Vec3& input_vec)
{
    x -= input_vec.x;
    y -= input_vec.y;
    z -= input_vec.z;
    return *this;
}

RT_Vec3 RT_Vec3::operator*(const double f) const
{
    RT_Vec3 g1(x * f, y * f, z * f);
    return g1;
}

RT_Vec3 RT_Vec3::operator*=(const double f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

double RT_Vec3::operator*(const RT_Vec3& input_vec) const
{
    return x * input_vec.x + y * input_vec.y + z * \
        input_vec.z;
}

RT_Vec3 RT_Vec3::operator/(const double f) const
{
    RT_Vec3 g1;
    if (f == 0.0f)
        return g1;
    g1.x = x / f;
    g1.y = y / f;
    g1.z = z / y;
    return g1;
}

RT_Vec3 RT_Vec3::operator/=(const double f)
{
    if (f == 0.0f)
        return *this;
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

bool RT_Vec3::operator<(const RT_Vec3& input_vec) const
{
    return length() < input_vec.length();
}

bool RT_Vec3::operator==(const RT_Vec3& input_vec) const
{
    if (abs(input_vec.x - x) > EPSILON_FOR_COMPARE)
        return false;
    if (abs(input_vec.y - y) > EPSILON_FOR_COMPARE)
        return false;
    if (abs(input_vec.z - z) > EPSILON_FOR_COMPARE)
        return false;
    return true;
}
