#pragma once

#include "v3.hpp"
#include "simobj.hpp"

class Rigidbody: public SimObj
{
public:
    static const V3 gravity;
    float mass;
    float translationalDrag;
    float rotationalDrag;
};
