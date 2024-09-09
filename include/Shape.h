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

	Shape(Shape* shape)
	{
		numVertices = shape->numVertices;
		distance = shape->distance;

		vertices = new vector3f[numVertices];
		normVec = new vector3f[numVertices];

		std::copy(shape->vertices, shape->vertices + shape->numVertices, this->vertices);
		std::copy(shape->normVec, shape->normVec + shape->numVertices, this->normVec);
	};

	Shape(const int numVertices, const float distance) : numVertices(numVertices), distance(distance), vertices(0), normVec(0)
	{
		vertices = new vector3f[numVertices];
		normVec = new vector3f[numVertices];
	};

	Shape(const int numVertices, vector3f* vertices, vector3f* normVec) : numVertices(numVertices), distance(0), vertices(vertices), normVec(normVec)
	{};

	~Shape()
	{
		delete[] vertices;
		delete[] normVec;
	};
};

#endif