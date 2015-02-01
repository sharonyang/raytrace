#ifndef RT_SHAPE_HPP
#define RT_SHAPE_HPP
#include <map>
#include <vector>
#include "RT_Sphere.hpp"
#include "RT_Object.hpp"

using namespace std;
class RT_Shape:public RT_Object
{
    private:
        RT_Sphere surround;
        bool intersectTriangle(const Ray& ray, \
            const RT_Vec3& v0, const RT_Vec3& v1, \
            const RT_Vec3&v2, double& dist, \
            RT_Vec3& normal);
        RT_Vec3 calNormal(const RT_Vec3& v0, \
            const RT_Vec3& v1, const RT_Vec3&v2) const;
    public:
        map<RT_Vec3,RT_Vec3> normals_map;
        vector<RT_Vec3> vertices;
        // Every 3 vertices = a face
        vector<int> indices;

        bool calSurround();
        void calNormalVectors();
        RT_Vec3 getNormal(const RT_Vec3&) const;
        INTERSECTION_TYPE isIntersected(const Ray& ray, double& dist);
};

#endif
