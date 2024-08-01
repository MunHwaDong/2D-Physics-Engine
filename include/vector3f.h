#ifndef VECTOR3F_H
#define VECTOR3F_H

class vector3f
{
public:
	float x;
	float y;
	float z;

	vector3f() : x(0), y(0), z(0)
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

	vector3f* operator+=(const vector3f& operand)
	{
		this->x += operand.x;
		this->y += operand.y;
		this->z += operand.z;

		return this;
	}

	vector3f* operator=(const vector3f& operand)
	{
		this->x = operand.x;
		this->y = operand.y;
		this->z = operand.z;
		
		return this;
	}

}; typedef vector3f Vector3f;

#endif