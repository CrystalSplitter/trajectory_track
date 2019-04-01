#pragma once

#include "v3.hpp"
#include "simobject.hpp"

class Rigidbody: public SimObject
{
public:
    Rigidbody();
    ~Rigidbody();
    
    // Public functions
    void fixedUpdate();

    // Public members
    float mass_;
    bool applyGravity_;
    V3 gravity_;
    V3 pos_;
    V3 velocity_;
    V3 angularVelocity_;
    float drag_;
    float angularDrag_;
};
