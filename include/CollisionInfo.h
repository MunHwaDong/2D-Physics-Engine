#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "vector3f.h"

class CollisionInfo
{
public:
    float min;
    vector3f edge;
    vector3f norm;

    CollisionInfo() : min(0), edge(), norm()
    {};

    void SetCollisionInfo(float min, vector3f norm)
    {
        this->min = min;
        this->norm = norm;
    }
};
#endif