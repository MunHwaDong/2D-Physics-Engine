#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <stdexcept>
#include <algorithm>

class vector4f
{
public:
	float x;
	float y;
	float z;
	float w;

	vector4f() : x(0), y(0), z(0), w(0)
	{};

	vector4f(int value) : x(value), y(value), z(value), w(value)
	{};

	vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{};

	vector4f(const vector4f& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w)
	{};

	~vector4f()
	{};

	const vector4f operator+(const vector4f& operand) const
	{
		return vector4f(this->x + operand.x, this->y + operand.y, this->z + operand.z, this->w + operand.w);
	}

	const vector4f operator+(const float operand) const
	{
		return vector4f(this->x + operand, this->y + operand, this->z + operand, this->w + operand);
	}

	const vector4f operator-(const vector4f& operand) const
	{
		return vector4f(this->x - operand.x, this->y - operand.y, this->z - operand.z, this->w - operand.w);
	}

	const vector4f operator-(const float operand) const
	{
		return vector4f(this->x - operand, this->y - operand, this->z - operand, this->w - operand);
	}

	const vector4f operator*(const float operand) const
	{
		return vector4f(this->x * operand, this->y * operand, this->z * operand, this->w * operand);
	}

	vector4f& operator+=(const vector4f& operand)
	{
		this->x += operand.x;
		this->y += operand.y;
		this->z += operand.z;
		this->w += operand.w;

		return *this;
	}

	vector4f& operator=(const vector4f& operand)
	{
		//자기 대입 방지
		if (this != &operand)
		{
			this->x = operand.x;
			this->y = operand.y;
			this->z = operand.z;
			this->w = operand.w;
		}

		return *this;
	}

	//To extension for Matrix
	float& operator[](const int idx)
	{
		if (idx >= 4 || idx < 0) std::out_of_range("Bad Input");

		if (idx == 0)
			return this->x;
		else if (idx == 1)
			return this->y;
		else if (idx == 2)
			return this->z;
		else
			return this->w;
	}

	//Output : Scalar
	const float DotProduct(const vector4f& operand) const
	{
		return (this->x * operand.x) + (this->y * operand.y) + (this->z * operand.z) + (this->w * operand.w);
	}

}; typedef vector4f vector4f;

#endif