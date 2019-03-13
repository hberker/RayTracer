#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
    private:
        float r,g,b;
        void Normalize();
    public:
        Color(float, float, float);
        Color();

        float getR();
        float getG();
        float getB();

        void setR(int);
        void setG(int);
        void setB(int);
};
Color::Color(float R, float G, float B) : r(R), g(G), b(B)
{
    Normalize();
}

Color::Color() : r(0), g(0), b(0) 
{}

void Color::Normalize()
{
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;

    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
}
float Color::getR()
{
    return r;
}
float Color::getG()
{
    return g;
}
float Color::getB()
{
    return b;
}

void Color::setR(int v)
{   
    r = v;
    Normalize();
}
void Color::setG(int v)
{       
    g = v;
    Normalize();
}
void Color::setB(int v)
{   
    b = v;
    Normalize();
}
#endif