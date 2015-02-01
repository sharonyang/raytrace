#include <cmath>
#include "include/DirectionalLight.hpp"
#include "include/RT_Object.hpp"

DirectionalLight::DirectionalLight() {}
DirectionalLight::DirectionalLight(const RT_Vec3& dir) : \
    m_Direction(dir) {}

void DirectionalLight::set_dir(const RT_Vec3& dir)
{
    m_Direction = dir;
}

RT_Vec3 DirectionalLight::get_dir() const
{
    return m_Direction;
}

RT_Vec3 DirectionalLight::ambient_calc(const RT_Vec3& material_Ka) const
{
    return RT_Vec3(m_Ka.x * material_Ka.x,
        m_Ka.y * material_Ka.y,
        m_Ka.z * material_Ka.z
        );
}

RT_Vec3 DirectionalLight::diffuse_calc(const RT_Vec3& material_Kd, \
    const RT_Vec3& normal, const RT_Vec3& rayDirection) const
{
    RT_Vec3 IdKd(m_Kd.x * material_Kd.x,
        m_Kd.y * material_Kd.y,
        m_Kd.z * material_Kd.z
         );
    double normalDotRay = normal * rayDirection;
    if (normalDotRay < 0.0f)
        normalDotRay = 0.0f;
    
    return IdKd*normalDotRay;
}

RT_Vec3 DirectionalLight::specular_calc(const RT_Vec3& material_Ks, \
    const RT_Vec3& normal, const RT_Vec3& rayDirection, \
    const RT_Vec3& cameraDirection, double material_shinness) const
{
    // Apply inverse square law here.
    RT_Vec3 IsKs(m_Ks.x * material_Ks.x,
        m_Ks.y * material_Ks.y,
        m_Ks.z * material_Ks.z
        );
    RT_Vec3 H = cameraDirection + rayDirection;
    H.normalize();
    double normalDotRay = normal * rayDirection;
    if (normalDotRay < 0.0f)
        normalDotRay = 0.0f;
    double normalDotH = normal * H;
    if (normalDotH < 0.0f)
        normalDotH = 0.0f;
    double normalDotHPowShinness = pow(normalDotH, material_shinness);
    if (normalDotRay <= 0.0f)
        normalDotHPowShinness = 0.0f;
    return IsKs * normalDotHPowShinness;
}

RT_Vec3 DirectionalLight::color_calc(const RT_Object* obj, \
    const RT_Vec3& point, const RT_Vec3& cameraPosition) const
{
    RT_Vec3 color(0.0f, 0.0f, 0.0f);
    RT_Vec3 normal = obj->getNormal(point);
    normal.normalize();
    RT_Vec3 ambient = ambient_calc(obj->getKa());
    RT_Vec3 rayDirection = get_dir() * -1.0f;
    rayDirection.normalize();
    RT_Vec3 diffuse = diffuse_calc(obj->getKd(), normal, rayDirection);
    RT_Vec3 cameraDirection = cameraPosition - point;
    cameraDirection.normalize();
    RT_Vec3 specular = specular_calc(obj->getKs(), normal, rayDirection, \
        cameraDirection, obj->getShininess());
    color = ambient + diffuse + specular;
    return color;
}

RT_Vec3 DirectionalLight::get_light_dir(const RT_Vec3& point) const
{
    return get_dir();
}
