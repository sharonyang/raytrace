#include <map>
#include <cstdlib>
#include <iostream>
#include "include/RT_Shape.hpp"


bool RT_Shape::calSurround()
{
    RT_Vec3 surroundCenter;
    double diameter;
    double maxx = -1000.0f, maxy = -1000.0f, maxz = -1000.0f, \
        minx = 1000.0f, miny = 1000.0f, minz = 1000.0f;
    if (vertices.empty())
        return false;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.at(i).x > maxx)
            maxx = vertices.at(i).x;
        if (vertices.at(i).y > maxy)
            maxy = vertices.at(i).y;
        if (vertices.at(i).z > maxz)
            maxz = vertices.at(i).z;
        if (vertices.at(i).x < minx)
            minx = vertices.at(i).x;
        if (vertices.at(i).y < miny)
            miny = vertices.at(i).y;
        if (vertices.at(i).z < minz)
            minz = vertices.at(i).z;
    }

    RT_Vec3 p1(minx, miny, minz);
    RT_Vec3 p2(maxx, maxy, maxz);
    diameter = (p2 - p1).length();
    surroundCenter = (p2 + p1) * 0.5;
    surround.setCenter(surroundCenter);
    surround.setRadius(diameter);
    
    return true;
}

RT_Vec3 RT_Shape::getNormal(const RT_Vec3& p) const
{
    std::map<RT_Vec3,RT_Vec3>::const_iterator iter;
    iter = normals_map.find(p);
    if (iter != normals_map.end())
    {
        return iter->second;
    } 
    else
        exit(1);
}

RT_Vec3 RT_Shape::calNormal(const RT_Vec3& v0, const RT_Vec3& v1, \
    const RT_Vec3& v2) const
{
    RT_Vec3 t1 = v1 - v0;
    RT_Vec3 t2 = v2 - v1;
    return t1.cross(t2);
}

bool RT_Shape::intersectTriangle(const Ray& ray, const RT_Vec3& v0, \
    const RT_Vec3& v1, const RT_Vec3& v2, double &dist, \
    RT_Vec3& normal)
{
    RT_Vec3 E1 = v1 - v0;
    RT_Vec3 E2 = v2 - v0;
    RT_Vec3 P = ray.get_direction().cross(E2);
    double det = E1 * P;
    RT_Vec3 T;
    if (det > 0)
        T = ray.get_origin() - v0;
    else
    {
        T = v0 - ray.get_origin();
        det = -det;
    }

    if (det < 0.0001f)
        return false;
    double u = T * P;
    if (u < 0.0f || u > det)
        return false;
    RT_Vec3 Q = T.cross(E1);
    double v = ray.get_direction() * Q;
    if (v < 0.0f || u + v > det)
        return false;
    double t = E2 * Q;
    double fInvDet = 1.0f / det;
    if (t < 0)
        return false;
    if (t*fInvDet < dist)
    {
        dist = t * fInvDet;
        normal = calNormal(v0, v1, v2);
        return true;
    }
    else
        return false;
}

INTERSECTION_TYPE RT_Shape::isIntersected(const Ray& ray,double &dist)
{
    double tmpdist = dist;
    if (surround.isIntersected(ray, tmpdist) == MISS)
        return MISS;
    bool result = false;
    RT_Vec3 tmpnormal;
    for (int i = 0; i < indices.size(); i += 3)
    {
        if (intersectTriangle(ray,vertices.at(indices.at(i)),
            vertices.at(indices.at(i + 1)),
            vertices.at(indices.at(i + 2)),
            dist,tmpnormal))
            result = true;
    }
    if (result)
    {
        RT_Vec3 p = ray.get_point(dist);
        std::map<RT_Vec3, RT_Vec3>::const_iterator iter;
        iter = normals_map.find(p);
        if (iter == normals_map.end())
            normals_map.insert(std::pair<RT_Vec3, RT_Vec3>(p, tmpnormal));
            return INTERSECTED_OUT;
    }
    else
        return MISS;
}
