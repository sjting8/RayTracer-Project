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

    /**
     * TODO: Implement the Ray intersection with the current geometry
     */

    /**
     * Once you find the intersection, add it to the `intersections` vector.
     *
     * Example:
     * Suppose the ray intersects the current geometry at a point `vec3 point`
     * at a distance `float t`, and the unit normal vector at the intersection
     * point is `vec3 normal`. You would then insert an intersection into the
     * vector as follows:
     *
     * intersections.push_back({t, point, normal, this, nullptr});
     *
     * Note:
     * - Here we pass the Model pointer as `nullptr` because it will be
     *   populated by the Model::intersect() function call.
     * - Only add intersections that are in front of the camera, i.e.,
     *   where t > 0.
     */

    /**
     * TODO: Update `intersections`
     */

     vec3 center = this->center;  // Assuming the sphere center is stored in this->center
     float radius = this->radius; // Assuming the sphere radius is stored in this->radius
 
     // Ray origin and direction (already in model space)
     vec3 ro = ray.p0;
     vec3 rd = normalize(ray.dir); // Ensure the direction is normalized
 
     // Vector from ray origin to sphere center
     vec3 oc = ro - center;
 
     // Coefficients for the quadratic equation
     float a = dot(rd, rd); // This should always be 1 if rd is normalized
     float b = 2.0f * dot(rd, oc);
     float c = dot(oc, oc) - radius * radius;
 
     // Discriminant
     float discriminant = b * b - 4 * a * c;
 
     if (discriminant < 0) {
         // No intersection
         return intersections;
     }
 
     // Compute the two possible solutions
     float sqrtDiscriminant = sqrt(discriminant);
     float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
     float t2 = (-b + sqrtDiscriminant) / (2.0f * a);
 
     // Check if the intersections are in front of the camera (t >= 0)
     if (t1 >= 0) {
         vec3 point = ro + t1 * rd;
         vec3 normal = normalize(point - center); // Normal in model space
         intersections.push_back({t1, point, normal, this, nullptr});
     }
 
     if (t2 >= 0 && t2 != t1) { // Avoid adding duplicate intersections
         vec3 point = ro + t2 * rd;
         vec3 normal = normalize(point - center); // Normal in model space
         intersections.push_back({t2, point, normal, this, nullptr});
     }
 
     return intersections;
};