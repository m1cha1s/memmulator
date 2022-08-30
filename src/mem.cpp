#include "mem.hpp"

namespace mulator::mem
{
    uint8_t Mem::get(size_t loc)
    {
        uint8_t value;
        this->memMap.get(loc, value);
        return value;
    }

    void Mem::set(size_t loc, uint8_t value)
    {
        this->memMap.set(loc, value);
    }
}