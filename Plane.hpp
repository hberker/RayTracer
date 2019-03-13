#ifndef PLANE_HPP
#define PLANE_HPP

#include <cmath>

#include "Object.hpp"
#include "Vect.hpp"
#include "Color.hpp"

class Plane : public Object
{
    private:
        Vect normal;
        double distance;       
        Color color;
        Vect center;

    public:
        Plane();
        Plane(Vect, double, Color, Vect);

        Vect getPlaneNormal();
        Vect getNormalAt(Vect point);

        double getPlaneDistance();
        double didIntersect(Ray);
        Color getColor();
};
Plane::Plane(Vect n, double d, Color c, Vect cent) : normal(n), distance(d), color(c), center(cent)
{

}

Color Plane::getColor()
{
    return color;
}
double Plane::didIntersect(Ray r) 
{
    return (normal-(r.getOrigin())).dot(normal) / normal.dot(r.getDirection());

}
Vect Plane::getPlaneNormal()
{
    return normal;
}
double Plane::getPlaneDistance()
{
    return distance;
}
#endif 