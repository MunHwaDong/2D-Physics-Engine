#include "RenderableObject.h"

void RenderableObject::UpdateVertices()
{
    //clock wise
    shape->vertices[0] = pos + vector3f(0, shape->distance, 0);

    shape->vertices[1] = pos + vector3f(shape->distance, -shape->distance, 0);

    shape->vertices[2] = pos + vector3f(-shape->distance, -shape->distance, 0);
}

void RenderableObject::UpdateNormVectors()
{
    int numVertex = shape->numVertices;

    for (int idx = 0; idx < numVertex; ++idx)
    {
        shape->normVec[idx] = Utill::Normalize(Utill::GetNormVector(shape->vertices[idx % numVertex], shape->vertices[(idx + 1) % numVertex]));
    }
}

void RenderableObject::UpdateObjAABB()
{
    objMinAABB = (pos + vector3f(-shape->distance, -shape->distance, 0));
    objMaxAABB = (pos + vector3f(shape->distance, shape->distance, 0));
}