#include "v3.hpp"

V3::V3(): x(0.0f), y(0.0f), z(0.0f)
{
    // Nothing to do here.
}

V3::V3(x, y, z): x(x), y(y), z(z)
{
    // Nothing to do here.
}

V3::~V3()
{
    // Nothing to do here.
}

V3 V3::add(V3& other)
{
   return V3(this->x + other.x, this->y + other.y, this->z + other.z); 
}

float V3::dot(V3& other)
{
   return this->x * other.x + this->y * other.y + this->z * other.z; 
}

V3 V3::scale(float other)
{
    return V3(other*this->x, other*this->y, other*this->z);
}

V3 V3::operator+(V3& other)
{
    return this->add(other);
}

V3 V3::operator-()
{
    return V3(-this->x, -this->y, -this->z);
}

V3 V3::operator-(V3& other)
{
    return this->add(-other);
}
