#include <fstream>
#include <cmath>

using namespace std;

class Color
{
    public:
        Color(){r=g=b=0;}
        Color(int R, int B, int G) : r(R), g(G), b(B) {}

        int r,g,b;
};
class Vect3f
{
    public:
        float x,y,z;
        Vect3f(){x=y=z=0;}
        Vect3f(float X,float Y, float Z) : x(X), y(Y), z(Z) {}

        Vect3f operator +(Vect3f v)
        {
            return Vect3f(x + v.x, y + v.y, z + v.z);
        }    
        Vect3f operator -(Vect3f v)
        {
            return Vect3f(x - v.x, y - v.y, z - v.z);
        } 
        Vect3f operator *(Vect3f v)
        {
            return Vect3f(x * v.x, y * v.y, z * v.z);
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
class Sphere
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

    const Color WHITE(255,255,255);
    const Color BLACK(0,0,0);
    Color c;
    Color pixel_col[HEIGHT][WIDTH];


    Sphere sphere(Vect3f(WIDTH/2, HEIGHT/2, 50), 20);


    
    initFile(&img, WIDTH, HEIGHT);

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            //Ray through each pixel
            Ray ray(Vect3f(row,col,0), Vect3f(0,0,1));
            
            double t = 20000;
            
            //Check for intersections
            if(sphere.intersect(ray,t))
            {
                writeOutPixel(&img, WHITE);
            }else
            {
                writeOutPixel(&img, BLACK);
            }
        }
    }
}
            /* TEST WRITING FILE -- WORKS
            c.r = row % 255;
            c.g = col % 255;
            c.b = (row * col) % 255;
            
            writeOutPixel(&img, c);
            */