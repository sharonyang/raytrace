#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP
#include "LightSource.hpp"
#include "RT_Object.hpp"
#include "RT_Vec3.hpp"

class PointLight : public LightSource
{
    public:
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

#endif /* end of include guard: POINTLIGHT_HPP */

