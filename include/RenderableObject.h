#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "Shape.h"

class RenderableObject : public IQTData
{
public:
    //center of obj
    vector3f pos;

    vector3f vel;
    vector3f accel;

    vector3f angularVel;
    vector3f angularAccel;

    //Store inverse of mass
    float inverseMass;

    bool isUseGravity;

    Shape* shape;

    RenderableObject() : pos(), vel(), accel(), angularVel(), angularAccel(), inverseMass(0), isUseGravity(true),  shape()
    {};

    RenderableObject(vector3f& pos) : pos(pos), vel(), accel(), angularVel(), angularAccel(), inverseMass(0), isUseGravity(true), shape()
    {};

    RenderableObject(vector3f& pos, float mass) : pos(pos), vel(), accel(), angularVel(), angularAccel(), inverseMass(1 / mass), isUseGravity(true), shape()
    {};

    RenderableObject(vector3f& pos, float mass, Shape* shape) : pos(pos), vel(), accel(), angularVel(), angularAccel(), inverseMass(1 / mass), isUseGravity(true), shape(shape)
    {};

    RenderableObject(vector3f& pos, float mass, bool isUseGravity, Shape* shape) : pos(pos), vel(), accel(), angularVel(), angularAccel(), inverseMass(1 / mass), isUseGravity(isUseGravity), shape(shape)
    {};

    ~RenderableObject()
    {};

    void UpdateVertices();
    void UpdateNormVectors();

    virtual const vector3f* const GetPosition() const override
    {
        return shape->vertices;
    }

    virtual const int GetDataCount() const override
    {
        return shape->numVertices;
    }
};

#endif