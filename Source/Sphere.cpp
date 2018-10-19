
#include "../Headers/Sphere.h"

Sphere::Sphere(): sphere_center(glm::vec4(0.0, 0.0, 0.0, 0.0)), radius(0.0){
}


Sphere::Sphere(vertex POSITION,float RADIUS){
    radius = RADIUS;
    sphere_center = POSITION;
}

void Sphere::set_t(float T){
    t = T;
}

//TODO: Add a type for the sphere (surface)
vertex Sphere::intersect(ray &arg) {
    float t0, t1;

    //A geometric solution for the intersection problem
    vertex rayOrigin = arg.startPoint();
    vertex rayEnd = arg.endPoint();
    glm::vec3 L = sphere_center - rayOrigin;
    glm::vec3 D = rayEnd - rayOrigin;

    float tca = glm::dot(L, D);

    //We use d2 = d^2 since it's easier to use for our calculations
    float d2 = dot(L, L) - tca*tca;

    //If d is greater than the radius of the sphere, the ray misses the sphere (overshoot)
    if(d2 >radius*radius)
        return vertex();

    float thc = sqrt(radius*radius - d2);

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
    return arg.getPointOnRay(t0);
}