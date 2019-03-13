#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Color.hpp"
#include "Ray.hpp"

class Object
{
    public:
        virtual double didIntersect(Ray) 
        {
            return 0;
        };
        virtual Color getColor()
        {
            return color;
        }
    private:
        Color color;
        
};



#endif