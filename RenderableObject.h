#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "Shape.h"

class RenderableObject
{
    public:
        //center of obj
        vector3f pos;

        vector3f vel;
        vector3f accel;

        vector3f angularVel;
        vector3f angularAccel;

        float mass;

        Shape shape;

        RenderableObject() : pos(), shape(), vel(), accel(), angularVel(), angularAccel(), mass(0)
        {};

        RenderableObject(vector3f& pos) : pos(pos), shape(), vel(), accel(), angularVel(), angularAccel(), mass(0)
        {};

        RenderableObject(vector3f& pos, float mass) : pos(pos), shape(), vel(), accel(), angularVel(), angularAccel(), mass(1/mass)
        {};

        RenderableObject(vector3f& pos, float mass, Shape& shape) : pos(pos), shape(shape), vel(), accel(), angularVel(), angularAccel(), mass(1/mass)
        {};

        ~RenderableObject()
        {};

        void UpdateVertices();
};

#endif
