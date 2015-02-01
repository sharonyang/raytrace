#ifndef LIGHTSOURCE_HPP
#define LIGHTSOURCE_HPP
#include "RT_Object.hpp"
#include "RT_Vec3.hpp"

class LightSource
{
    protected:
        RT_Vec3 m_Position;
        // ambient
        RT_Vec3 m_Ka;
        // diffuse
        RT_Vec3 m_Kd;
        // specular
        RT_Vec3 m_Ks;
    public:
        LightSource();
        LightSource(const RT_Vec3& pos, const RT_Vec3& ka, \
            const RT_Vec3& kd, const RT_Vec3& ks);
        void setPosition(const RT_Vec3&);
        void setKa(const RT_Vec3&);
        void setKd(const RT_Vec3&);
        void setKs(const RT_Vec3&);
        RT_Vec3 getPosition() const;
        RT_Vec3 getKa() const;
        RT_Vec3 getKd() const;
        RT_Vec3 getKs() const;
        virtual RT_Vec3 ambient_calc(const RT_Vec3& material_Ka) \
            const = 0;
        virtual RT_Vec3 diffuse_calc(const RT_Vec3& material_Kd, \
            const RT_Vec3& normal, const RT_Vec3& rayDirection) const = 0;
        virtual RT_Vec3 specular_calc(const RT_Vec3& material_Ks, 
            const RT_Vec3& normal, const RT_Vec3& rayDirection, 
            const RT_Vec3& cameraDirection, double material_shinness) \
            const = 0;
        virtual RT_Vec3 color_calc(const RT_Object* obj, \
            const RT_Vec3& point, const RT_Vec3& cameraPosition) const = 0;
        virtual RT_Vec3 get_light_dir(const RT_Vec3& point) const = 0;
};

#endif
