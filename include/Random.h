/*
 * Random.h
 *
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include "reflex/types.h"

namespace reflex{

class Random
{
public:
     Random(uint16 seed);
     uint16 next(uint16 limit);

private:
     uint16 seed;
};

}
#endif
