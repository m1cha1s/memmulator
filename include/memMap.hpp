#pragma once

#include <vector>
#include <stddef.h>
#include <inttypes.h>
#include <memory>
#include <string>

namespace mulator::mem
{
    class MemMapEntry
    {
    protected:
        size_t start, end;

    public:
        bool active(size_t loc)
        {
            return (loc >= start && loc < end);
        }

        size_t toRelative(size_t loc)
        {
            return loc - this->start;
        }

        size_t getStart()
        {
            return start;
        }

        size_t getEnd()
        {
            return end;
        }

        virtual std::string getName() = 0;
        virtual uint8_t get(size_t relativeLoc) = 0;
        virtual void set(size_t relativeLoc, uint8_t val) = 0;
    };

    class MemMap
    {
    private:
        std::vector<std::shared_ptr<MemMapEntry>> entries;
        std::shared_ptr<MemMapEntry> findEntry(size_t loc);

    public:
        MemMap() {}
        ~MemMap() {}

        template <typename T, typename... Args>
        void addEntry(Args &&...args)
        {
            entries.push_back(std::make_shared<T>(args...));
        }

        std::string dumpEntries();

        bool get(size_t loc, uint8_t &val);
        bool get(size_t loc, uint16_t &val);
        bool get(size_t loc, uint32_t &val);
        bool get(size_t loc, uint64_t &val);

        bool set(size_t loc, uint8_t val);
        bool set(size_t loc, uint16_t val);
        bool set(size_t loc, uint32_t val);
        bool set(size_t loc, uint64_t val);
    };
}