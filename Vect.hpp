#ifndef VECT_HPP
#define VECT_HPP

class Vect
{
    public:
        Vect(float xVal, float yVal, float zVal);
        Vect();

        float x,y,z;

        double dot(Vect);
        Vect negative();
        Vect operator +(Vect);
        Vect operator -(Vect);
        Vect operator *(double);


};
Vect::Vect(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

Vect::Vect() : x(0), y(0), z(0) {}

Vect Vect::negative()
{
   return Vect(-x,-y,-z);
}
double Vect::dot(Vect v)
{
    return (v.x * x + v.y * y + v.z * z);
}
Vect Vect::operator +(Vect v)
{
    return Vect(x + v.x, y + v.y, z + v.z);
}    
Vect Vect::operator -(Vect v)
{
    return Vect(x - v.x, y - v.y, z - v.z);
} 
Vect Vect::operator *(double s)
{
    return Vect(x * s, y * s, z * s);
} 



#endif