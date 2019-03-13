#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>

#include "Vect.hpp"
#include "Color.hpp"
#include "Sphere.hpp"
#include "Object.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "FileWriter.hpp"

using namespace std;

Vect pixelToViewport(Vect pixel, float invWidth, float invHeight,float aspectratio) 
{
    float fov = 30.0;
    float angle = tan(0.5 * fov * M_PI/ 180.0);
    float vx = (2 * ((pixel.x + 0.5) * invWidth) - 1) * angle * aspectratio;
    float vy = (1 - 2 * ((pixel.y + 0.5) * invHeight)) * angle;
    Vect rayDirection  = Vect(vx, vy, pixel.z);
    rayDirection.normalize();
    return rayDirection;
}


int main()
{
    const int HEIGHT(800);
    const int WIDTH(800);
    const float aspectratio = WIDTH / float(HEIGHT);
    const float invWidth = 1/WIDTH;
    const float invHeight = 1/HEIGHT;

    const char* filename("rayT.ppm");

    const Color BLACK(0,0,0);
    const Color WHITE(255,255,255);
    const Color RED(255,0,0);
    const Color GREEN(0,255,0);
    const Color BLUE(0,0,255);
     
    const Vect camLoc(0, 0 , -20); 
    Sphere SPHERE_RED(Vect(0, 0, 15),13, RED);

    
    const vector<Object*> SCENE_OBJECTS = vector<Object*>{};

    FileWriter fw = FileWriter(filename, HEIGHT, WIDTH);

    for(int x = -(WIDTH / 2); x < WIDTH / 2; x++)
    {
        for(int y = -HEIGHT / 2; y < HEIGHT / 2; y++)
        {
            Vect point(x,y,1);
            Vect dir = point - camLoc;//pixelToViewport(point,invWidth,invHeight,aspectratio);
           // dir.normalize();
            Ray castRay(camLoc, dir);
            //cout<< dir.x << " " << dir.y << " " << dir.z << endl;
            if((SPHERE_RED.didIntersect(castRay)) != -1)
            {
                cout << SPHERE_RED.findIntersection(castRay) << endl;
                Color newC = SPHERE_RED.getColor();
                fw.writeOutPixel(newC);
            }else
            {
                fw.writeOutPixel(BLACK);
            }
            
        }
    }

    cout << "FINISHED" << endl;

    return 0;
}