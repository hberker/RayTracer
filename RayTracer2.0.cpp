#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;


double clampDouble255(double d)
{
    if (d > 255)
    {
        return 255;
    }else if (d < 0)
    {
        return 0;
    }
    return d;
}
class Color
{
    public:
        Color(){r=g=b=0;}
        Color(int R, int G, int B) : r(R), g(G), b(B) {}

        Color lighten(double scale)
        {
            return Color(clampDouble255(r + scale),clampDouble255(g + scale), clampDouble255(b + scale));
        }
        bool operator==(Color c)
        {
            return (r = c.r && g == c.g && b == c.b);
        }
        Color operator+(double d)
        {
            return Color(clampDouble255(r+d), clampDouble255(g+d),clampDouble255(b+d));
        }
        Color operator*(double d)
        {
            return Color(clampDouble255(r*d), clampDouble255(g*d),clampDouble255(b*d));
        }
        Color operator-(double d)
        {
            return Color(clampDouble255(r -d), clampDouble255(g-d), clampDouble255(b-d));
        }
        int r,g,b;
};
class Vect3f
{
    public:
        float x,y,z;
        Vect3f(){x=y=z=0;}
        Vect3f(float X,float Y, float Z) : x(X), y(Y), z(Z) {}
        Vect3f Negative()
        {
            return Vect3f(-x,-y,-z);
        }
        Vect3f operator +(Vect3f v)
        {
            return Vect3f(x + v.x, y + v.y, z + v.z);
        }    
        Vect3f operator -(Vect3f v)
        {
            return Vect3f(x - v.x, y - v.y, z - v.z);
        } 
        Vect3f operator *(double s)
        {
            return Vect3f(x * s, y * s, z * s);
        } 
};
double dot(Vect3f v, Vect3f b)
{
    return (v.x * b.x + v.y * b.y + v.z * b.z);
}
class Ray
{
    public:
        Vect3f origin;
        Vect3f direction;
        Ray(Vect3f o, Vect3f d) : origin(o), direction(d) {}
};
class Object
{
    public:
        virtual bool intersect(Ray, double&) 
        {
            return false;
        };
        virtual bool findIntersection(Ray r)
        {
            return false;
        }

        virtual Color getColor()
        {
            return Color(255,255,255);
        }
        //Color color = Color(255,255,255);
        
};
class Sphere : public Object
{
    public:
        Vect3f center;
        Color color;
        double radius;
        
        Sphere(Vect3f c, double r) : center(c), radius(r) {}
        Sphere(Vect3f c, double r, Color col) : center(c), radius(r), color(col) {}
        
        bool intersect(Ray ray, double &t)
        {
            Vect3f orig = ray.origin;
            Vect3f dir = ray.direction;
            Vect3f oc = orig-center;
            
            double b = 2 * dot(oc, dir);
            double c = dot(oc,oc) - (radius*radius);
            double disc = b*b-4*c;

            if (disc < 0) return false;
            else
            {
                disc = sqrt(disc);
                
                double t0 = -b-disc;
                double t1 = -b+disc;

                t = (t0 < t1) ? t0 : t1;
                return true;
            }
        }
        Color getColor()
        {
            return color;
        }
        bool findIntersection(Ray r)
        {
            Vect3f ray_origin = r.origin;

            double ray_origin_x = ray_origin.x;
            double ray_origin_y = ray_origin.y;
            double ray_origin_z = ray_origin.z;

            Vect3f ray_direction = r.direction;
            double ray_direction_x = ray_direction.x;
            double ray_direction_y = ray_direction.y;
            double ray_direction_z = ray_direction.z;

            Vect3f sphere_center = center;
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
                    return true;
                }
                else
                {
                    //the second is the smallest postive root
                    double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
                    return root_2;
                    return true;
                }
            }else 
            {
                //the ray missed the sphere
                return -1;
                return false;
            } 
        } 


};
class Plane : public Object
{
    public:
        Plane();

        Plane(Vect3f n, double d, Color c) : normal(n), distance(d), color(c) {}

        Vect3f getPlaneNormal(){ return normal;};
        double getPlaneDistance(){return distance;}
        Color getPlaneColor() {return color;}
        Vect3f getNormalAt(Vect3f point);

        Vect3f normal;
        double distance;
        Color color;
        bool findIntersection(Ray r)
        {
            Vect3f ray_direction = r.origin;
            double a  = dot(ray_direction, normal);

            if(a == 0)
            {
                //ray is parallel to the plane
                return -1;
                return false;

            }else
            {
                /* Ray Intersects Plane */
                double b = dot(normal, (r.origin + (normal * distance).Negative()));
                return -1*b/a;
                return true;

            }
        }
        bool intersect(Ray r, double &t)
        {
            Vect3f ray_direction = r.origin;
            double a  = dot(ray_direction, normal);

            if(a == 0)
            {
                //ray is parallel to the plane
                return false;
            }else
            {
                double b = dot(normal, (r.origin + (normal * distance).Negative()));
                if( -1*b/a > 1000)
                {
                    return false;
                }
                /* Ray Intersects Plane */
                return true;
            }
        }
        Color getColor()
        {
            return color;
        }
};
int initFile(ofstream *img, const int WIDTH, const int HEIGHT)
{
    *img << "P3"<< endl;
    *img << WIDTH << " " << HEIGHT << endl;
    *img << "255" << endl; 
}
int writeOutPixel(ofstream *img, Color c)
{
    *img << c.r << " " << c.g << " " << c.b << endl;
}
double clamp(double val, double min, double max )
{
    if(val < min) return min;
    if(val > max) return max;
    return val;
}
int main()
{

    const int WIDTH = 800, HEIGHT = 800;
    const char *filename = "atest.ppm";
    
    ofstream img = ofstream(filename);
    initFile(&img, WIDTH, HEIGHT);

    const Color WHITE(255,255,255);
    const Color BLACK(0,0,0);
    const Color GREEN(0,255,0);
    const Color RED(255,0,0);
    Color SKY_BLUE(40,60,92);

    Object *sphere;
    Object *plane;

    sphere = new Sphere(Vect3f(WIDTH/2, HEIGHT/2, -1000000), 50, RED);
    //light = new Sphere(Vect3f(0, 0, 50), 1, WHITE);
    plane = new Plane(Vect3f(.001, .00000000000001, 19), 1, GREEN);

   
    //ORDERED BY IMPORTANCE IN SCENE
    const vector<Object*> SCENE_OBJECTS = {sphere, plane};
    

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {

            Ray ray(Vect3f(row,col,0), Vect3f(0,0, -1));
            double t = 20000;
            bool NOHIT = true;

            for(Object *obj : SCENE_OBJECTS)
            {
                if(NOHIT)
                {
                    if(obj->intersect(ray, t))
                    {
                        writeOutPixel(&img, obj->getColor());
                        NOHIT = false;
                    }
                }
            }
            if (NOHIT) writeOutPixel(&img, SKY_BLUE.lighten(row / 2));
        }
    
    }
    return 0;
}

            