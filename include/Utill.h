#ifndef UTILL_H
#define UTILL_H

#include "vector3f.h"
#include "Matrix3f.h"

class Utill
{
private:
    //객체 생성 방지
    Utill() {};

public:
    static const vector3f GetNormVector(const vector3f& operand1, const vector3f& operand2, bool isCCW = true)
    {
        if(isCCW)
            return vector3f(-(operand1.y - operand2.y), operand1.x - operand2.x, operand1.z - operand2.z);
        else //CW
            return vector3f(operand1.y - operand2.y, -(operand1.x - operand2.x), operand1.z - operand2.z);
    }

    static const Matrix3f GetTranslateMatrix(const vector3f& translate)
    {
        return Matrix3f(
                        vector3f(1.0f, 0.0f, translate.x),
                        vector3f(0.0f, 1.0f, translate.y),
                        vector3f(0.0f, 0.0f, 1.0f)
        );
    }

    static const Matrix3f GetRotateMatrix(const float theta)
    {
        return Matrix3f(
            vector3f(cos(theta), -sin(theta), 0),
            vector3f(sin(theta), cos(theta), 0),
            vector3f(0.0f, 0.0f, 1.0f)
        );

    }

    static const Matrix3f GetScaleMatrix(const vector3f& scale)
    {
        return Matrix3f(
                        vector3f(scale.x, 0.0f, 0.0f),
                        vector3f(0.0f, scale.y, 0.0f),
                        vector3f(0.0f, 0.0f, 1.0f));
    }
};

#endif