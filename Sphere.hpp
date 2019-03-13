#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "Object.hpp"
#include "Vect.hpp"

class Sphere : public Object
{
    
    public:
        Sphere(Vect c, double r) : center(c), radius(r) {}
        Sphere(Vect c, double r, Color col) : center(c), radius(r), color(col) {}
        
        double didIntersect(Ray);
        Vect getCenter();
        double getRadius();
        Color getColor();
        double findIntersection(Ray r)
        {
            Vect ray_origin = r.getOrigin();

            double ray_origin_x = ray_origin.x;
            double ray_origin_y = ray_origin.y;
            double ray_origin_z = ray_origin.z;

            Vect ray_direction = r.getDirection();
            double ray_direction_x = ray_direction.x;
            double ray_direction_y = ray_direction.y;
            double ray_direction_z = ray_direction.z;

            Vect sphere_center = center;
            double sphere_center_x = sphere_center.x;
            double sphere_center_y = sphere_center.y;
            double sphere_center_z = sphere_center.z;

            double a = 1;
            double b = (2*(ray_origin_x - sphere_center_x) * ray_direction_x) + (2*(ray_origin_y - sphere_center_y) * ray_direction_y) + (2*(ray_origin_z - sphere_center_z) * ray_direction_z);
            double c = std::pow(ray_origin_x - sphere_center_x, 2) + std::pow(ray_origin_y - sphere_center_y, 2) + std::pow(ray_origin_z - sphere_center_z, 2) - (radius * radius);

            double discriminant = b*b - 4*c;

            if (discriminant > 0)
            {
                // the ray intersects the sphere


                //the first root
                double root_1 = ((-1*b - sqrt(discriminant)) / 2) - 0.000001;
                
                if (root_1 > 0)
                {
                    //the first root is the smallest positive root
                    return root_1;
                }
                else
                {
                    //the second is the smallest postive root
                    double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
                    return root_2;
                }
            }else 
            {
                //the ray missed the sphere
                return -1;
            } 
        } 
        
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

double Sphere::didIntersect(Ray r) 
{
    /*RETURNS T -- distance from insterct or NaN if no intersect*/
    Vect oc = r.getOrigin() - center ;
    double a = r.getDirection().dot(r.getDirection());
    double b = 2 * (oc.dot(r.getDirection()));
    double c = (oc.dot(oc)) - (radius * radius);
    double disc = b*b-4*c;
    double t = -1;
    if (disc < 0) return -1;
        else
        {
            disc = sqrt(disc); 
            double t0 = -b-disc;
            double t1 = -b+disc;
            t = (t0 < t1) ? t0 : t1;
            return t;
        }    
}

#endif