#ifndef GOBJECT_HPP
#define GOBJECT_HPP
#include "RT_Vec3.hpp"
#include "Ray.hpp"

enum INTERSECTION_TYPE {INTERSECTED_IN = -1, MISS = 0, INTERSECTED_OUT = 1};

class RT_Object
{
    private:
        // ambient material
        RT_Vec3 m_Ka;
        // diffuse material
        RT_Vec3 m_Kd;
        // specular material
        RT_Vec3 m_Ks;
        double m_Shininess;
        double m_Reflectivity;
        double m_Transparency;
    public:
        RT_Object();
        RT_Object(const RT_Vec3&, const RT_Vec3&, \
            const RT_Vec3&, double, double, double);
        void setKa(const RT_Vec3&);
        void setKd(const RT_Vec3&);
        void setKs(const RT_Vec3&);
        void setShininess(double);
        void setReflectivity(double);
        void setTransparency(double);
        RT_Vec3 getKa() const;
        RT_Vec3 getKd() const;
        RT_Vec3 getKs() const;
        double getShininess() const;
        double getReflectivity() const;
        double getTransparency() const;
        virtual RT_Vec3 getNormal(const RT_Vec3&) const=0;
        virtual INTERSECTION_TYPE isIntersected(const Ray&, \
            double&) = 0;
};

#endif
