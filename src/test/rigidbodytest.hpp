#include "../physics/rigidbody.hpp"

int rigidbodyTest() {
    Rigidbody rigidbody;
    for (size_t i = 0; i < 100; ++i) {
        rigidbody.fixedUpdate();
        std::cout << "x: " << rigidbody.pos_.x
            << " y: " << rigidbody.pos_.y
            << " z: " << rigidbody.pos_.z
            << " ay: " << rigidbody.velocity_.y
            << std::endl;
    }
    return 0;
}
