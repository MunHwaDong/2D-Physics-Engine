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

    vector3f theta;

    vector3f angularVel;
    vector3f angularAccel;

    //for collision detection (Square)
    vector3f objMinAABB;
    vector3f objMaxAABB;

    //Store inverse of mass
    float inverseMass;

    bool isUseGravity;

    Shape* shape;

    //for test
    std::string name;

    RenderableObject() : pos(), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(0), isUseGravity(true), shape()
    {};

    RenderableObject(vector3f& pos) : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(0), isUseGravity(true), shape()
    {};

    RenderableObject(vector3f& pos, float mass)
        : pos(pos), vel(), accel(), theta(theta), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(1 / mass), isUseGravity(true), shape()
    {};

    RenderableObject(vector3f& pos, vector3f& theta, float mass)
        : pos(pos), vel(), accel(), theta(theta), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(1 / mass), isUseGravity(true), shape()
    {};

    //tmp code -> test for transform
    RenderableObject(float mass, Shape* shape)
        : pos(), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(1 / mass), isUseGravity(true), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    RenderableObject(vector3f& pos, float mass, Shape* shape)
        : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(1 / mass), isUseGravity(true), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    RenderableObject(vector3f& pos, vector3f& theta, float mass, bool isUseGravity, Shape* shape)
        : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(1 / mass), isUseGravity(isUseGravity), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    ~RenderableObject()
    {};

    void UpdateVertices();
    void UpdateNormVectors();
    void UpdateObjAABB();

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