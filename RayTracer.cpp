#include <fstream>
#include <cmath>

using namespace std;


class Color
{
    public:
        Color(){r=g=b=0;}
        Color(int R, int G, int B) : r(R), g(G), b(B) {}

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
class Object
{
    public:
        Vect3f center;
        
};
class Ray
{
    public:
        Vect3f origin;
        Vect3f direction;
        Ray(Vect3f o, Vect3f d) : origin(o), direction(d) {}
};
class Sphere : public Object
{
    public:
        Vect3f center;
        double radius;
        Sphere(Vect3f c, double r) : center(c), radius(r) {}
        
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
        double findIntersection(Ray r)
        {
            Vect3f ray_direction = r.origin;
            double a  = dot(ray_direction, normal);

            if(a == 0)
            {
                //ray is parallel to the plane
                return -1;

            }else
            {
                /* Ray Intersects Plane */
                double b = dot(normal, (r.origin + (normal * distance).Negative()));
                return -1*b/a;

            }
        }
        bool didIntersect(Ray r)
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
int main()
{
    const int WIDTH = 800, HEIGHT = 800;
    const char *filename = "atest.ppm";
    
    ofstream img = ofstream(filename);
    initFile(&img, WIDTH, HEIGHT);

    const Color WHITE(255,255,255);
    const Color BLACK(0,0,0);
    const Color GREEN(0,255,0);

    Sphere sphere(Vect3f(WIDTH/2, HEIGHT/2, -1000000), 50);
    Sphere light(Vect3f(0, 0, 50), 1);
    Plane plane(Vect3f(.001, .00000000000001, 19), 1, GREEN);
    //Sphere sphereTwo(Vect3f(WIDTH/5, HEIGHT/4, 5), 50);

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            //Ray through each pixel
            Ray ray(Vect3f(row,col,0), Vect3f(0,0, -1));
            
            double t = 20000;
            
            //Check for intersections
            if(sphere.intersect(ray,t))
            {

                //Point of Intersection
                Vect3f pi =  ray.origin + ray.direction * t;
                
                //Light intersection
                
                writeOutPixel(&img, WHITE);
            }
            else if (plane.didIntersect(ray))
            {
                writeOutPixel(&img, GREEN);
            }else
            {
                writeOutPixel(&img, BLACK);
            }
        }
    }
    return 0;
}
            