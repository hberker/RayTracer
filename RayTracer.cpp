#include <fstream>

using namespace std;

class Color
{
    public:
        int r,g,b;
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
    Color c;
    ofstream img = ofstream(filename);
    
    initFile(&img, WIDTH, HEIGHT);

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            c.r = row % 255;
            c.g = col % 255;
            c.b = (row * col) % 255;
            
            writeOutPixel(&img, c);
        }
    }
}