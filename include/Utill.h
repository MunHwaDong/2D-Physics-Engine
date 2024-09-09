#ifndef UTILL_H
#define UTILL_H

#include "Matrix3f.h"
#include "Matrix4f.h"

class Utill
{
private:
    //객체 생성 방지
    Utill() {};

public:
    enum { WORLD_MIN = -10000,
           WORLD_MAX = 10000};

    static const vector3f GetNormVector(const vector3f& operand1, const vector3f& operand2, bool isCCW = true)
    {
        if (isCCW)
            return vector3f(-(operand1.y - operand2.y), operand1.x - operand2.x, operand1.z - operand2.z);
        else //CW
            return vector3f(operand1.y - operand2.y, -(operand1.x - operand2.x), operand1.z - operand2.z);
    }

    static const vector3f Normalize(const vector3f& operand)
    {
        float len = operand.length();

        if (len > 0.0f)
        {
            return vector3f(operand.x / len, operand.y / len, operand.z / len);
        }

        // 길이가 0인 벡터는 그대로 반환
        return operand;
    }

    static const Matrix4f GetTranslateMatrix4f(const vector3f& translate)
    {
        return Matrix4f(
            vector4f(1.0f, 0.0f, 0.0f, translate.x),
            vector4f(0.0f, 1.0f, 0.0f, translate.y),
            vector4f(0.0f, 0.0f, 1.0f, translate.z),
            vector4f(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix4f GetRotateMatrix4f(const float theta, const vector3f& axis)
    {
        float c = cos(theta);
        float s = sin(theta);
        float t = 1.0f - c;

        // Normalize the axis vector
        vector3f normalizedAxis = Normalize(axis);
        float x = normalizedAxis.x;
        float y = normalizedAxis.y;
        float z = normalizedAxis.z;

        return Matrix4f(
            vector4f(t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0.0f),
            vector4f(t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0.0f),
            vector4f(t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0.0f),
            vector4f(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix4f GetZRotateMatrix4f(const float theta)
    {
        return Matrix4f(
            vector4f(cos(theta), -sin(theta), 0.0f, 0.0f),
            vector4f(sin(theta), cos(theta), 0.0f, 0.0f),
            vector4f(0.0f, 0.0f, 1.0f, 0.0f),
            vector4f(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix4f GetScaleMatrix4f(const vector3f& scale)
    {
        return Matrix4f(
            vector4f(scale.x, 0.0f, 0.0f, 0.0f),
            vector4f(0.0f, scale.y, 0.0f, 0.0f),
            vector4f(0.0f, 0.0f, scale.z, 0.0f),
            vector4f(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix3f GetIdentityMatrix3f()
    {
        return Matrix3f(
            vector3f(1.0f, 0.0f, 0.0f),
            vector3f(0.0f, 1.0f, 0.0f),
            vector3f(0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix4f GetIdentityMatrix4f()
    {
        return Matrix4f(
            vector4f(1.0f, 0.0f, 0.0f, 0.0f),
            vector4f(0.0f, 1.0f, 0.0f, 0.0f),
            vector4f(0.0f, 0.0f, 1.0f, 0.0f),
            vector4f(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix4f GetModelMatrix(const vector3f& transVec, const vector3f& scaleVec, float theta = 0)
    {
        return Utill::GetScaleMatrix4f(scaleVec) * Utill::GetRotateMatrix4f(theta, vector3f(0.0f, 0.0f, 1.0f)) * Utill::GetTranslateMatrix4f(transVec);
    }

    static const Matrix4f GetModelMatrixTF(const vector3f& transVec, const vector3f& scaleVec, float theta = 0)
    {
        return Utill::GetTranslateMatrix4f(transVec) * Utill::GetRotateMatrix4f(theta, vector3f(0.0f, 0.0f, 1.0f)) * Utill::GetScaleMatrix4f(scaleVec);
    }
};

#endif