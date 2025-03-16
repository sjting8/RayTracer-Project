#include "GeomSphere.h"

#include <iostream>
#include <utility>

#include "Intersection.h"
#include "Ray.h"

std::vector<Intersection> GeomSphere::intersect(Ray &ray) {
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */
    using namespace glm;

    // vector to store the intersections
    std::vector<Intersection> intersections;

    vec3 center = this->center;
    float radius = this->radius;

    vec3 ro = ray.p0;
    vec3 rd = normalize(ray.dir);

    vec3 oc = ro - center;

    float a = dot(rd, rd);
    float b = 2.0f * dot(rd, oc);
    float c = dot(oc, oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return intersections;
    }

    float sqrtDiscriminant = sqrt(discriminant);
    float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
    float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

    if (t1 >= 0.0f) {
        vec3 point = ro + t1 * rd;
        vec3 normal = normalize(point - center);

        // Ensure normal is correctly calculated
        if (length(normal) == 0.0f) {
            std::cerr << "Warning: Zero-length normal detected." << std::endl;
        }

        intersections.push_back({t1, point, normal, this, nullptr});
    }

    if (t2 >= 0.0f && t1 != t2) { // Ensure t1 and t2 are different
        vec3 point = ro + t2 * rd;
        vec3 normal = normalize(point - center);

        // Ensure normal is correctly calculated
        if (length(normal) == 0.0f) {
            std::cerr << "Warning: Zero-length normal detected." << std::endl;
        }

        intersections.push_back({t2, point, normal, this, nullptr});
    }

    return intersections;
};