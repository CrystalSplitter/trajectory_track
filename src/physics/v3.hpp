#pragma once

class V3
{
public:
    V3();
    V3(float x, float y, float z);
    ~V3();
    float x;
    float y;
    float z;
    V3 add(V3& other);
    V3 scale(V3& other);
    float dot(V3& other);
    /**
     * This is just an alias for add().
     */
    V3 operator+(V3& other);
    V3 operator-();
    V3 operator-(V3& other);
};
