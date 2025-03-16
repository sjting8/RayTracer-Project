#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include "GeomTriangle.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Intersection.h"
#include "Ray.h"

GeomTriangle::GeomTriangle(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

std::vector<Intersection> GeomTriangle::intersect(Ray &ray) {
    using namespace glm;

    std::vector<Intersection> intersections;

    vec3 v0 = vertices[0];
    vec3 v1 = vertices[1];
    vec3 v2 = vertices[2];

    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;

    vec3 h = cross(ray.dir, edge2);
    float a = dot(edge1, h);

    if (a > -0.00001f && a < 0.00001f) {
        return intersections; // Ray is parallel to triangle
    }

    float f = 1.0f / a;
    vec3 s = ray.p0 - v0;
    float u = f * dot(s, h);

    if (u < 0.0f || u > 1.0f) {
        return intersections;
    }

    vec3 q = cross(s, edge1);
    float v = f * dot(ray.dir, q);

    if (v < 0.0f || u + v > 1.0f) {
        return intersections;
    }

    float t = f * dot(edge2, q);

    if (t > 0.00001f) { // Intersection!
        vec3 intersectionPoint = ray.p0 + ray.dir * t;
        vec3 normal = normalize(cross(edge1, edge2));

        intersections.push_back({t, intersectionPoint, normal, this, nullptr});
    }

    return intersections;
}