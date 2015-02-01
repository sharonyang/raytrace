#ifndef RAYTRACING_HPP
#define RAYTRACING_HPP
#include "main.hpp"

using namespace std;
RT_Vec3 ray_trace(const Ray& ray, int left)
{
    // background
    RT_Vec3 color(0.0f, 0.0f, 0.0f);
    double distance = MAX_DISTANCE;
    double shade = 1.0f;
    int IntersectionObject = -1;
    INTERSECTION_TYPE tmp;
    for (int k = 0; k < object_list.size(); k++)
    {
        RT_Object* obj = object_list.at(k);
        if ((tmp = obj->isIntersected(ray, distance)) != MISS)
            IntersectionObject = k;
    }
    if (IntersectionObject == -1)
        return color;
    
    // Now there is a intersection point
    RT_Object* obj = object_list.at(IntersectionObject);
    RT_Vec3 point = ray.get_point(distance);
    RT_Vec3 tmpColor;
    RT_Vec3 objMaterial = obj->getKa();
    color = RT_Vec3(globalLight.x * objMaterial.x,
        globalLight.y * objMaterial.y,
        globalLight.z * objMaterial.z);
    
    for (int k = 0; k < light_list.size(); k++)
    {
        LightSource* ls = light_list.at(k);
        bool flag = true;
        RT_Vec3 curr_objRayDirection = \
            ls->get_light_dir(point) * (-1.0f);
        RT_Vec3 tracePoint = point;
        while (flag && shade >= EPSILON) 
        {
            flag = false;
            Ray curr_objRay(tracePoint + curr_objRayDirection * EPSILON, \
                curr_objRayDirection);
            int tmpIntersectionObject = -1;
            distance = MAX_DISTANCE;
            for (int t = 0; t < object_list.size(); t++)
            {
                RT_Object* obj = object_list.at(t);
                if ((tmp = obj->isIntersected(curr_objRay, distance)) != MISS)
                    tmpIntersectionObject = t;
            }

            if (tmpIntersectionObject != -1)
            {
                shade *= object_list.at(\
                    tmpIntersectionObject)->getTransparency();
                tracePoint=curr_objRay.get_point(distance);
                flag = true;
            }
        }
        if (shade < EPSILON)
            shade = 0.0f;
        tmpColor = ls->color_calc(obj, point, cam_position);
        tmpColor *= shade;
        color += tmpColor;
    }
    
    if (left == 0)
        return color * (1-obj->getReflectivity() - \
            obj->getTransparency());
    
    RT_Vec3 normal = obj->getNormal(point);
    normal.normalize();
    RT_Vec3 rd = ray.get_direction();
    RT_Vec3 transparentRayDirection = rd;
    Ray transparentRay(point + transparentRayDirection * EPSILON, \
        transparentRayDirection);
    RT_Vec3 transparentColor = ray_trace(transparentRay, left - 1);
    
    // Reflect
    RT_Vec3 reflectRayDirection = rd-normal * (rd * normal) * 2.0f;
    Ray reflectRay(point + reflectRayDirection * EPSILON, \
        reflectRayDirection);
    RT_Vec3 reflectColor = ray_trace(reflectRay, left - 1);

    color = color * (1-obj->getReflectivity() - obj->getTransparency()) + \
        RT_Vec3(objMaterial.x * reflectColor.x, \
            objMaterial.y * reflectColor.y, \
            objMaterial.z*reflectColor.z) * obj->getReflectivity() + \
        RT_Vec3(objMaterial.x * transparentColor.x, \
            objMaterial.y * transparentColor.y, \
            objMaterial.z * transparentColor.z) * \
        obj->getTransparency();

    return color;
}

#endif
