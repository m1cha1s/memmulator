#pragma once

#include <inttypes.h>
#include <stddef.h>

#include "memMap.hpp"

namespace mulator::mem
{
    class Mem
    {
    private:
        MemMap memMap;

    public:
        Mem() {}
        Mem(MemMap memMap)
        {
            this->memMap = memMap;
        }
        ~Mem() {}

        uint8_t get(size_t loc);
        void set(size_t loc, uint8_t value);
    };
}