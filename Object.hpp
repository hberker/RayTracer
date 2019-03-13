#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Color.hpp"
#include "Ray.hpp"

class Object
{
    public:
        virtual bool didIntersect(Ray) 
        {
            return false;
        };
        virtual Color getColor()
        {
            return color;
        }
    private:
        Color color;
        
};



#endif