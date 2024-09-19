#ifndef IQTDATA_H
#define IQTDATA_H

#include "vector3f.h"

class IQTData
{
    public:
        virtual const vector3f* const GetPosition() const = 0;
        virtual const int GetDataCount() const = 0;
        virtual ~IQTData() = 0;
};

#endif