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
    V3 add(const V3& other) const;
    V3 scale(const float other) const;
    float dot(const V3& other) const;
    /**
     * This is just an alias for add().
     */
    V3 operator+(const V3& other) const;
    V3 operator-() const;
    V3 operator-(const V3& other) const;
};
