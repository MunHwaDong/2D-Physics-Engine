#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <stdexcept>
#include <algorithm>

class vector3f
{
public:
	float x;
	float y;
	float z;

	vector3f() : x(0), y(0), z(0)
	{};

	vector3f(int value) : x(value), y(value), z(value)
	{};

	vector3f(float x, float y, float z) : x(x), y(y), z(z)
	{};

	vector3f(const vector3f& vector) : x(vector.x), y(vector.y), z(vector.z)
	{};

	~vector3f()
	{};

	const vector3f operator+(const vector3f& operand) const
	{
		return vector3f(this->x + operand.x, this->y + operand.y, this->z + operand.z);
	}

	const vector3f operator+(const float operand) const
	{
		return vector3f(this->x + operand, this->y + operand, this->z + operand);
	}

	const vector3f operator-(const vector3f& operand) const
	{
		return vector3f(this->x - operand.x, this->y - operand.y, this->z - operand.z);
	}

	const vector3f operator-(const float operand) const
	{
		return vector3f(this->x - operand, this->y - operand, this->z - operand);
	}

	const vector3f operator*(const float operand) const
	{
		return vector3f(this->x * operand, this->y * operand, this->z * operand);
	}

	vector3f& operator+=(const vector3f& operand)
	{
		this->x += operand.x;
		this->y += operand.y;
		this->z += operand.z;

		return *this;
	}

	vector3f& operator=(const vector3f& operand)
	{
		//자기 대입 방지
		if(this != &operand)
		{
			this->x = operand.x;
			this->y = operand.y;
			this->z = operand.z;
		}
		
		return *this;
	}

	//To extension for Matrix
	float& operator[](const int idx)
	{
		if(idx >= 3) std::out_of_range("Bad Input");

		if(idx == 0)
			return this->x;
		else if(idx == 1)
			return this->y;
		else
			return this->z;
	}

	//Output : Scalar
	const float DotProduct(const vector3f& operand) const
	{
		return (this->x * operand.x) + (this->y * operand.y) + (this->z * operand.z);
	}

}; typedef vector3f Vector3f;

#endif