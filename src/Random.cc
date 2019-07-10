#include "Random.h"
using namespace reflex;

Random::Random(uint16 seed){
    this->seed = seed;
}

uint16 Random::next(uint16 limit){
    seed = (seed * 32719 + 3) % 32719;
    return ((seed % limit) + 1);
}
