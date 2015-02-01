#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP
#include "LightSource.hpp"
#include "RT_Object.hpp"
#include "RT_Vec3.hpp"

class DirectionalLight : public LightSource
{
    private:
        RT_Vec3 m_Direction;
    public:
        DirectionalLight();
        DirectionalLight(const RT_Vec3& dir);
        void set_dir(const RT_Vec3& dir);
        RT_Vec3 get_dir() const;
        RT_Vec3 ambient_calc(const RT_Vec3& material_Ka) const;
        RT_Vec3 diffuse_calc(const RT_Vec3& material_Kd, \
            const RT_Vec3& normal, const RT_Vec3& rayDirection) const;
        RT_Vec3 specular_calc(const RT_Vec3& material_Ks, \
            const RT_Vec3& normal, const RT_Vec3& rayDirection, \
            const RT_Vec3& cameraDirection, double material_shinness) const;
        RT_Vec3 color_calc(const RT_Object* obj, const RT_Vec3& point, \
            const RT_Vec3& cameraPosition) const;
        RT_Vec3 get_light_dir(const RT_Vec3& point) const;
};

#endif
