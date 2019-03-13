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



int main()
{
    const int HEIGHT(800);
    const int WIDTH(800);
    const char* filename("thisworks.ppm");

    const Color BLACK(0,0,0);
    const Color WHITE(255,255,255);
    const Color RED(255,0,0);
    const Color GREEN(0,255,0);
    const Color BLUE(0,0,255);

    const vector<Object*> SCENE_OBJECTS = vector<Object*>{};

    FileWriter fw = FileWriter(filename, HEIGHT, WIDTH);

    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            fw.writeOutPixel(BLACK);
        }
    }

    cout << "FINISHED" << endl;

    return 0;
}