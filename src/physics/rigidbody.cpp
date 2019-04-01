#include "rigidbody.hpp"
#include <math.h>

Rigidbody::Rigidbody():
    mass_(1.0f),
    applyGravity_(true),
    gravity_(V3(0.0f, -9.81f, 0.0f)),
    pos_(V3()),
    velocity_(V3()),
    angularVelocity_(V3()),
    drag_(0.01f)
{
    // Nothing to do here.
}

Rigidbody::~Rigidbody()
{
    // Nothing to do here.
}

void Rigidbody::fixedUpdate()
{
    // Update position.
    pos_ = pos_ + velocity_.scale(SimObject::deltaTime);
    
    // Update velocity.
    if (applyGravity_) {
        velocity_ = velocity_ + gravity_;
    }

    // Apply drag.
    V3 dragForce(
            copysign(drag_*pow(velocity_.x, 2.0f), velocity_.x),
            copysign(drag_*pow(velocity_.y, 2.0f), velocity_.y),
            copysign(drag_*pow(velocity_.z, 2.0f), velocity_.z));
    velocity_ = velocity_ - dragForce;
}


