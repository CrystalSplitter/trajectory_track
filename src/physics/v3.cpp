#include "v3.hpp"
#include <math.h>

V3::V3(): x(0.0f), y(0.0f), z(0.0f)
{
    // Nothing to do here.
}

V3::V3(float x, float y, float z): x(x), y(y), z(z)
{
    // Nothing to do here.
}

V3::~V3()
{
    // Nothing to do here.
}

V3 V3::add(const V3& other) const
{
   return V3(this->x + other.x, this->y + other.y, this->z + other.z); 
}

float V3::dot(const V3& other) const
{
   return this->x * other.x + this->y * other.y + this->z * other.z; 
}

V3 V3::scale(const float other) const
{
    return V3(other*this->x, other*this->y, other*this->z);
}

V3 V3::operator+(const V3& other) const
{
    return this->add(other);
}

V3 V3::operator-() const
{
    return V3(-this->x, -this->y, -this->z);
}

V3 V3::operator-(const V3& other) const
{
    return this->add(-other);
}
