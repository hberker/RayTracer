#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"
#include "Vect.hpp"

class Sphere : public Object
{
    
    public:
        Sphere(Vect c, double r) : center(c), radius(r) {}
        Sphere(Vect c, double r, Color col) : center(c), radius(r), color(col) {}
        
        bool findIntersection(Ray r);
        bool didIntersect(Ray);
        Vect getCenter();
        double getRadius();
        Color getColor();
        
    private:
        Vect center;
        double radius;
        Color color;
    
};
Vect Sphere::getCenter()
{
    return center;
}
double Sphere::getRadius()
{
    return radius;
}
Color Sphere::getColor()
{
    return color;
}
bool Sphere::didIntersect(Ray) 
{
    /*RETURNS T -- distance from insterct or NaN if no intersect*/
    Vect oc = r.origin.subtract(center);
    double a = r.direction.dot(r.direction);
    double b = 2.0 * oc.dot(r.direction);
    double c = oc.dot(oc) - (radius * radius);

    return (-b - sqrt(b*b - 4*a*c)) / (a * 2.0);
}

#endif