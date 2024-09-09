#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "vector3f.h"

class CollisionInfo
{
public:
    double o1Min;
    double o2Min;
    vector3f o1Norm;
    vector3f o2Norm;

    CollisionInfo() : o1Min(0.0), o2Min(0.0), o1Norm(0), o2Norm(0)
    {};

    CollisionInfo(double o1Min, double o2Min, vector3f o1Norm, vector3f o2Norm) :
        o1Min(o1Min), o2Min(o2Min), o1Norm(o1Norm), o2Norm(o2Norm)
    {};

    void SetCollisionInfo(double o1Min, double o2Min, vector3f o1Norm, vector3f o2Norm)
    {
        this->o1Min = o1Min;
        this->o1Min = o2Min;
        this->o1Norm = o1Norm;
        this->o2Norm = o2Norm;
    }
};
#endif