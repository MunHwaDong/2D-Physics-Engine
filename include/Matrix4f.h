#ifndef MATRIX4F_H
#define MATRIX4F_H

#include "vector4f.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Definition of 3x3 Matrix
class Matrix4f
{

public:
    mutable vector4f mat4[4];

    Matrix4f()
    {
        mat4[0] = vector4f(0);
        mat4[1] = vector4f(0);
        mat4[2] = vector4f(0);
        mat4[3] = vector4f(0);
    };

    Matrix4f(const vector4f& row1, const vector4f& row2, const vector4f& row3, const vector4f& row4)
    {
        mat4[0] = row1;
        mat4[1] = row2;
        mat4[2] = row3;
        mat4[3] = row4;
    }

    Matrix4f(const Matrix4f& matrix)
    {
        std::copy(std::begin(matrix.mat4), std::end(matrix.mat4), std::begin(mat4));
    }

    ~Matrix4f()
    {};

    const Matrix4f operator+(const Matrix4f& operand) const
    {
        Matrix4f result;

        std::transform(std::begin(mat4), std::end(mat4), std::begin(operand.mat4), std::begin(result.mat4),
            [](const vector4f& lhs, const vector4f& rhs) { return lhs + rhs; });

        return result;
    }

    const Matrix4f operator-(const Matrix4f& operand) const
    {
        Matrix4f result;

        std::transform(std::begin(mat4), std::end(mat4), std::begin(operand.mat4), std::begin(result.mat4),
            [](const vector4f& lhs, const vector4f& rhs) { return lhs - rhs; });

        return result;
    }

    //Linear Transform
    const vector4f operator*(const vector4f& operand) const
    {
        return vector4f(
            this->mat4[0].DotProduct(operand),
            this->mat4[1].DotProduct(operand),
            this->mat4[2].DotProduct(operand),
            this->mat4[3].DotProduct(operand)
        );
    }

    //For Local to World Coordinate
    //In : 3D-Vec
    const vector3f Transform(const vector3f& operand) const
    {
        float x = this->mat4[0][0] * operand.x + this->mat4[0][1] * operand.y + this->mat4[0][2] * operand.z + this->mat4[0][3];
        float y = this->mat4[1][0] * operand.x + this->mat4[1][1] * operand.y + this->mat4[1][2] * operand.z + this->mat4[1][3];
        float z = this->mat4[2][0] * operand.x + this->mat4[2][1] * operand.y + this->mat4[2][2] * operand.z + this->mat4[2][3];
        float w = this->mat4[3][0] * operand.x + this->mat4[3][1] * operand.y + this->mat4[3][2] * operand.z + this->mat4[3][3];

        return vector3f(x / w, y / w, z / w);
    }

    //Matrix Multiplication
    const Matrix4f operator*(const Matrix4f& operand) const
    {
        Matrix4f result;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                float sum = 0.0f;
                for (int k = 0; k < 4; ++k)
                {
                    sum += this->mat4[row][k] * operand.mat4[k][col];
                }
                result.mat4[row][col] = sum;
            }
        }

        return result;
    }

    //복사와 대입은 다르기에 복사 생성자와 다르게 구현함.
    Matrix4f& operator=(const Matrix4f operand)
    {
        if (this != &operand)
        {
            for (int idx = 0; idx < 4; ++idx)
            {
                mat4[idx] = operand[idx];
            }
        }

        return *this;
    }

    //Get Matrix entity
    const vector4f& operator[](const int row) const
    {
        if (row >= 4) throw std::out_of_range("Bad Input");
        else return mat4[row];
    }

    // glm::mat4로 변환하는 메서드
    glm::mat4 TransGlmMat4() const {
        return glm::mat4(
            mat4[0][0], mat4[0][1], mat4[0][2], mat4[0][3],
            mat4[1][0], mat4[1][1], mat4[1][2], mat4[1][3],
            mat4[2][0], mat4[2][1], mat4[2][2], mat4[2][3],
            mat4[3][0], mat4[3][1], mat4[3][2], mat4[3][3]
        );
    }

}; typedef Matrix4f matrix4f;

#endif