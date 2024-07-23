#include "RenderableObject.h"

void RenderableObject::UpdateVertices()
{
    //clock wise
    shape.vertices[0] = pos + vector3f(0, shape.distance, 0);

    shape.vertices[1] = pos + vector3f(shape.distance, -shape.distance, 0);

    shape.vertices[2] = pos + vector3f(-shape.distance, -shape.distance, 0);
}