#define EPSILON_FOR_COMPARE 0.000001

#ifndef RT_VEC3_HPP
#define RT_VEC3_HPP
#include <iostream>

using namespace std;
class RT_Vec3
{
    public:  
        double x;
        double y;
        double z;
    public:
        friend ostream& operator<<(ostream&, const RT_Vec3&);
        friend istream& operator>>(istream&, RT_Vec3&);
        RT_Vec3();
        RT_Vec3(const RT_Vec3&);
        RT_Vec3(double, double, double);
        double length() const;

        // this returns false if length is 0.
        bool normalize();
        RT_Vec3 cross(const RT_Vec3&);
        bool operator<(const RT_Vec3&) const;
        RT_Vec3 operator=(const RT_Vec3&);
        RT_Vec3 operator=(double);
        RT_Vec3 operator+(const RT_Vec3&) const;
        RT_Vec3 operator+=(const RT_Vec3&);
        RT_Vec3 operator-(const RT_Vec3&) const;
        RT_Vec3 operator-=(const RT_Vec3&);
        RT_Vec3 operator*(const double) const;
        RT_Vec3 operator*=(const double);
        double operator*(const RT_Vec3&) const;
        RT_Vec3 operator/(const double) const;
        RT_Vec3 operator/=(const double);
        bool operator==(const RT_Vec3&) const;
};

#endif
