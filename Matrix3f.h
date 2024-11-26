#ifndef MATRIX3F_H
#define MATRIX3F_H

#include "vector3f.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Definition of 3x3 Matrix
class Matrix3f
{

public:
    mutable vector3f mat3[3];

    Matrix3f()
    {};

    Matrix3f(const vector3f& row1, const vector3f& row2, const vector3f& row3)
    {
        mat3[0] = row1;
        mat3[1] = row2;
        mat3[2] = row3;
    }

    Matrix3f(const Matrix3f& matrix)
    {
        std::copy(std::begin(matrix.mat3), std::end(matrix.mat3), std::begin(mat3));
    }

    ~Matrix3f()
    {};

    const Matrix3f operator+(const Matrix3f& operand) const
    {
        Matrix3f result;

        std::transform(std::begin(mat3), std::end(mat3), std::begin(operand.mat3), std::begin(result.mat3),
            [](const vector3f& lhs, const vector3f& rhs) { return lhs + rhs; });

        return result;
    }

    const Matrix3f operator-(const Matrix3f& operand) const
    {
        Matrix3f result;

        std::transform(std::begin(mat3), std::end(mat3), std::begin(operand.mat3), std::begin(result.mat3),
            [](const vector3f& lhs, const vector3f& rhs) { return lhs - rhs; });

        return result;
    }

    //Linear Transform
    const vector3f operator*(const vector3f& operand) const
    {
        return vector3f(
            this->mat3[0].DotProduct(operand),
            this->mat3[1].DotProduct(operand),
            this->mat3[2].DotProduct(operand)
        );
    }

    //For Local to World Coordinate
    const vector3f Transform(const vector3f& operand) const
    {
        float x = this->mat3[0][0] * operand.x + this->mat3[0][1] * operand.y + this->mat3[0][2];
        float y = this->mat3[1][0] * operand.x + this->mat3[1][1] * operand.y + this->mat3[1][2];
        float w = this->mat3[2][0] * operand.x + this->mat3[2][1] * operand.y + this->mat3[2][2];

        return vector3f(x / w, y / w, 0);
    }

    //Matrix Multiplication
    const Matrix3f operator*(const Matrix3f& operand) const
    {
        Matrix3f result;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                float sum = 0.0f;
                for (int k = 0; k < 3; ++k)
                {
                    sum += this->mat3[row][k] * operand.mat3[k][col];
                }
                result.mat3[row][col] = sum;
            }
        }

        return result;
    }

    //복사와 대입은 다르기에 복사 생성자와 다르게 구현함.
    Matrix3f& operator=(const Matrix3f operand)
    {
        if (this != &operand)
        {
            for (int idx = 0; idx < 3; ++idx)
            {
                mat3[idx] = operand[idx];
            }
        }

        return *this;
    }

    //Get Matrix entity
    const vector3f& operator[](const int row) const
    {
        if (row >= 3) throw std::out_of_range("Bad Input");
        else return mat3[row];
    }

    // glm::mat3로 변환하는 메서드
    glm::mat3 TransGlmMat3() const {
        return glm::mat3(
            mat3[0][0], mat3[0][1], mat3[0][2],
            mat3[1][0], mat3[1][1], mat3[1][2],
            mat3[2][0], mat3[2][1], mat3[2][2]
        );
    }

}; typedef Matrix3f matrix3f;

#endif