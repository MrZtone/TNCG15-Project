
#include "../Headers/Sphere.h"

Sphere::Sphere(): sphere_center(glm::vec4(0.0, 0.0, 0.0, 1.0), nullptr, nullptr, -1), radius(0.0){
}


Sphere::Sphere(vertex POSITION,float RADIUS, colordbl c){
    radius = RADIUS;
    sphere_center = POSITION;
    s_color = c;
}

void Sphere::set_t(float T){
    t = T;
}

//TODO: Add a type for the sphere (surface)

vertex Sphere::intersect(ray &arg) {
    float t0, t1;

    //A geometric solution for the intersection problem
    //vertex rayOrigin = arg.startPoint();
    //vertex rayEnd = arg.endPoint();
    //glm::vec3 L = glm::vec3(sphere_center.coordinates - rayOrigin.coordinates);
    //glm::vec3 D = glm::normalize(glm::vec3(rayEnd.coordinates - rayOrigin.coordinates));

    glm::vec3 intersection(0.0f);
    glm::vec3 normal(0.0f);
    glm::vec3 origin = arg.startPoint().coordinates;
    glm::vec3 dir = glm::normalize(glm::vec3(arg.endPoint().coordinates - arg.startPoint().coordinates));
    glm::vec3 center = sphere_center.coordinates;

    if(glm::intersectRaySphere(origin, dir, center, radius, intersection, normal))
        return vertex(glm::vec4(intersection, 1.0f), &s_color, new direction(normal), vertex::SPECULAR);
    else
        return vertex();
    /*
    float tca = glm::dot(L, D);
    if (tca < 0.0f) // the center of the sphere is behind the origin of the ray
        return  vertex();

    //We use d2 = d^2 since it's easier to use for our calculations
    float d2 = dot(L, L) - tca*tca;

    //If d is greater than the radius of the sphere, the ray misses the sphere (overshoot)
    if(d2 >radius*radius)
        return vertex();

    float thc = sqrtf(radius*radius - d2);

    //Our two solutions to the quadratic problem we get by doing a geometric solution!
    t0 = tca - thc;
    t1 = tca + thc;

    //Now we implement our boundaries to determine how we actually intersect with the sphere
    if(t0 > t1)
        std::swap(t0, t1);

    if(t0 < 0){
        t0 = t1; //If t0<0 we just use t1 instead.
        if(t0 < 0)
            return vertex(); //This means that even t1 is negative, then we're surely not intersecting
    }

    //glm::vec4 endpoint = arg.getPointOnRay(t0);
    glm::vec4 endpoint = glm::vec4((glm::vec3(arg.startPoint().coordinates) + t0*D), 1.0f);
    glm::vec3 norm = glm::normalize(glm::vec3(endpoint-sphere_center.coordinates));
    return vertex(endpoint, &s_color, (new direction(norm)), vertex::SPECULAR);
    */
}
