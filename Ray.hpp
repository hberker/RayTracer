#ifndef RAY_HPP
#define RAY_HPP

#include "Vect.hpp"

class Ray
{
    private:
        Vect origin;
        Vect direction;
    public:
        Ray(Vect o, Vect d) : origin(o), direction(d) {}
        Vect getOrigin();
        Vect getDirection();
};
Vect Ray::getDirection()
{
    return origin;
}
Vect Ray::getOrigin()
{
    return direction;
}
#endif