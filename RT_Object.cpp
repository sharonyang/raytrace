#include "include/RT_Object.hpp"

RT_Object::RT_Object() : m_Shininess(0.0f), m_Reflectivity(0.0f) {}

RT_Object::RT_Object(const RT_Vec3& ka, const RT_Vec3& kd, \
    const RT_Vec3& ks, double shi, double ref, double tra) :
    m_Ka(ka), m_Kd(kd), m_Ks(ks), m_Shininess(shi), \
    m_Reflectivity(ref), m_Transparency(tra) {}

void RT_Object::setKa(const RT_Vec3& ka)
{
    m_Ka = ka;
}

void RT_Object::setKd(const RT_Vec3& kd)
{
    m_Kd = kd;
}

void RT_Object::setKs(const RT_Vec3& ks)
{
    m_Ks = ks;
}

void RT_Object::setShininess(double shi)
{
    m_Shininess = shi;
}

void RT_Object::setReflectivity(double ref)
{
    m_Reflectivity = ref;
}

void RT_Object::setTransparency(double tra)
{
    m_Transparency = tra;
}

RT_Vec3 RT_Object::getKa() const
{
    return m_Ka;
}

RT_Vec3 RT_Object::getKd() const
{
    return m_Kd;
}

RT_Vec3 RT_Object::getKs() const
{
    return m_Ks;
}

double RT_Object::getShininess() const
{
    return m_Shininess;
}

double RT_Object::getReflectivity() const
{
    return m_Reflectivity;
}

double RT_Object::getTransparency() const
{
    return m_Transparency;
}
