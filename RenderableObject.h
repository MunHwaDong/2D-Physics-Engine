#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include <vector>

class RenderableObject
{
    public:
        std::vector<float> pos;

        std::vector<float> vel;
        std::vector<float> accel;

        std::vector<float> angularVel;
        std::vector<float> angularAccel;

        float mass;

        RenderableObject() : pos(2), vel(2), accel(2), angularVel(2), angularAccel(2), mass(0)
        {};

        ~RenderableObject()
        {};

        void ApplyForce(const std::vector<float>& force)
        {
            //x
            accel[0] += force[0] / mass;
            //y
            accel[1] += force[1] / mass;
        }
};

#endif