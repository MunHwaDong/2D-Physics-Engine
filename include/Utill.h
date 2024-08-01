#ifndef UTILL_H
#define UTILL_H

#include "vector3f.h"

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
};

#endif