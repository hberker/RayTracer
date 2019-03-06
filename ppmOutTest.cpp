#include "stdio.h"
#include <fstream>
using namespace std;
struct Color
{
    int r,g,b;
};
void writeImageFOPEN(char *name, int WIDTH, int HEIGHT)
{
    FILE *fp = fopen(name, "wb");
    Color *color;
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            static unsigned char color[3];
            color[0] = row % 256;  /* red */
            color[1] = col % 256;  /* green */
            color[2] = (row * col) % 256;  /* blue */
            (void) fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
}
int writeImageFSTREAM(const char *name, int WIDTH, int HEIGHT)
{
    ofstream img(name);
    Color c;
    /* Init File lines*/
    img << "P3"<< endl;
    img << WIDTH << " " << HEIGHT << endl;
    img << "255" << endl; 

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            c.r = row % 255;
            c.g = col % 255;
            c.b = (row * col) % 255;
            img << c.r << " " << c.g << " " << c.b << endl;
        }
    }
    return 0;
}
int Smain()
{
    const int WIDTH = 800, HEIGHT = 800;
    const char *filename = "test.ppm";
    writeImageFSTREAM(filename, WIDTH, HEIGHT);
    return 0;
}