#pragma once

class SimObject
{
    
public:
    
    SimObject();
    ~SimObject();
    // Time between last update and current update.
    // May need to be variable to work on one thread.
    static constexpr float deltaTime = 0.1f;
    virtual void fixedUpdate();
    
};
