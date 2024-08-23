#ifndef SHAPE_H
#define SHAPE_H

#include "vector3f.h"
#include "vector4f.h"

#include "Utill.h"
#include "IQTData.h"

class Shape
{
public:
	int numVertices;
	float distance;

	vector3f* vertices;
	vector3f* normVec;

	Shape() : numVertices(0), distance(0), vertices(0), normVec(0)
	{};

	Shape(const int numVertices, const float distance) : numVertices(numVertices), distance(distance), vertices(0), normVec(0)
	{
		vertices = new vector3f[numVertices];
		normVec = new vector3f[numVertices];
	};

	Shape(const int numVertices, const float distance, vector3f* vertices, vector3f* normVec) : numVertices(numVertices), distance(distance), vertices(vertices), normVec(normVec)
	{
		vertices = new vector3f[numVertices];
		normVec = new vector3f[numVertices];
	};

	~Shape()
	{
		delete[] vertices;
		delete[] normVec;
	};
};

#endif