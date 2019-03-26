#include "rigidbody.hpp"

Rigibody::physUpdate()
{
    this->pos_ = this->pos_ + Rigidbody::gravity();
}
