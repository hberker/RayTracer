#ifndef VECT_HPP
#define VECT_HPP
#include <cmath>
using namespace std;
class Vect
{
    public:
        Vect(float xVal, float yVal, float zVal);
        Vect();

        float x,y,z;

        double dot(Vect);
        Vect negative();
        Vect normalize();
        Vect operator +(Vect);
        Vect operator -(Vect);
        Vect operator *(double);
        float length2() const { return x * x + y * y + z * z; }
        float length() const { return sqrt(length2()); }


};
Vect::Vect(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

Vect::Vect() : x(0), y(0), z(0) {}

Vect Vect::normalize() { 
      float norm2 = length2();
      if(norm2 > 0) {
        float invNorm = 1 / sqrt(norm2);
        x *= invNorm, y *= invNorm, z *= invNorm;
      }
      return *this;
}
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