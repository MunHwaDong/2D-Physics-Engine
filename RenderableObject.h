#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "Shape.h"
#include <string>
#include <vector>

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

    float mass;
    //Store inverse of mass
    float inverseMass;

    bool isUseGravity;

    Shape* shape;

    //for test
    std::string name;

    RenderableObject() : pos(), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), inverseMass(0), isUseGravity(true), shape()
    {};

    //copy constructor
    RenderableObject(RenderableObject* obj) : pos(obj->pos), vel(obj->vel), accel(obj->accel), theta(obj->theta), angularVel(obj->angularVel),
        angularAccel(obj->angularAccel), objMinAABB(obj->objMinAABB), objMaxAABB(obj->objMaxAABB), mass(obj->mass), inverseMass(obj->inverseMass), isUseGravity(obj->isUseGravity), shape(), name(obj->name)
    {
        shape = new Shape(obj->shape);
    };

    RenderableObject(vector3f& pos, float mass)
        : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), mass(mass), inverseMass(1 / mass), isUseGravity(true), shape()
    {};

    //tmp code -> test for transform
    RenderableObject(float mass, Shape* shape)
        : pos(), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), mass(mass), inverseMass(1 / mass), isUseGravity(true), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    RenderableObject(float mass, bool isUseGravity, Shape* shape)
        : pos(), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), mass(mass), inverseMass(1 / mass), isUseGravity(isUseGravity), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    RenderableObject(vector3f& pos, float mass, Shape* shape)
        : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), mass(mass), inverseMass(1 / mass), isUseGravity(true), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    RenderableObject(vector3f& pos, float mass, bool isUseGravity, Shape* shape)
        : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), mass(mass), inverseMass(1 / mass), isUseGravity(isUseGravity), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    RenderableObject(vector3f& pos, vector3f& theta, float mass, bool isUseGravity, Shape* shape)
        : pos(pos), vel(), accel(), theta(), angularVel(), angularAccel(), objMinAABB(), objMaxAABB(), mass(mass), inverseMass(1 / mass), isUseGravity(isUseGravity), shape(shape)
    {
        UpdateVertices();
        UpdateNormVectors();
        UpdateObjAABB();
    };

    ~RenderableObject()
    {
        delete shape;
    };

    void UpdateVertices();
    void UpdateNormVectors();
    void UpdateObjAABB();
    const vector3f GetEdge(const int idx) const;

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