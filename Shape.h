#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <iostream>

struct vector3f
{
	float x;
	float y;
	float z;

	vector3f() : x(0), y(0), z(0)
	{};

	vector3f(float x, float y, float z) : x(x), y(y), z(z)
	{};

	vector3f(const vector3f& vector) : x(vector.x), y(vector.y), z(vector.z)
	{};

	vector3f& operator+(const vector3f& operand) const
	{
		vector3f result(this->x + operand.x, this->y + operand.y, this->z + operand.z);
		
		return result;
	}

	vector3f& operator+(const vector3f& operand)
	{
		return const_cast<vector3f&>(static_cast<const vector3f&>(*this) + operand);
	}

	vector3f operator+(const float operand) const
	{
		vector3f result;

		result.x = this->x + operand;
		result.y = this->y + operand;
		result.z = this->z + operand;

		return result;
		//return vector3f(this->x + operand, this->y + operand, this->z + operand);
	}

	vector3f operator*(const float operand) const
	{
		vector3f result;

		result.x = this->x * operand;
		result.y = this->y * operand;
		result.z = this->z * operand;

		return result;
		//return vector3f(this->x * operand, this->y * operand, this->z * operand);
	}

	void operator+=(const vector3f& operand)
	{
		this->x += operand.x;
		this->y += operand.y;
		this->z += operand.z;
	}

}; typedef vector3f Vector3f;


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