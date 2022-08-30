#include <memory>

#include "memMap.hpp"

namespace mulator::mem
{
    std::string MemMap::dumpEntries()
    {
        std::string result = "==== Entry dump ====\n";

        for (size_t i = 0; i < entries.size(); i++)
        {
            result += "Name:  " + entries[i]->getName() + "\n";
            result += "Start: " + std::to_string(entries[i]->getStart()) + "\n";
            result += "End:   " + std::to_string(entries[i]->getEnd()) + "\n";
            result += "--------------------\n";
        }

        return result;
    }

    std::shared_ptr<MemMapEntry> MemMap::findEntry(size_t loc)
    {
        for (size_t i = 0; i < this->entries.size(); i++)
        {
            if (this->entries[i]->active(loc))
            {
                return this->entries[i];
            }
        }
        return NULL;
    }

    bool MemMap::get(size_t loc, uint8_t &val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        val = entry->get(entry->toRelative(loc));

        return true;
    }

    bool MemMap::get(size_t loc, uint16_t &val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        // Check if all bytes fit in the entry
        for (int i = 1; i < 2; i++)
            if (entry != this->findEntry(loc + i))
                return false;

        val = (uint16_t)entry->get(entry->toRelative(loc));
        val |= ((uint16_t)entry->get(entry->toRelative(loc + 1))) << 8;

        return true;
    }

    bool MemMap::get(size_t loc, uint32_t &val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        // Check if all bytes fit in the entry
        for (int i = 1; i < 4; i++)
            if (entry != this->findEntry(loc + i))
                return false;

        val = (uint32_t)entry->get(entry->toRelative(loc));
        val |= ((uint32_t)entry->get(entry->toRelative(loc + 1))) << 8;
        val |= ((uint32_t)entry->get(entry->toRelative(loc + 2))) << 16;
        val |= ((uint32_t)entry->get(entry->toRelative(loc + 3))) << 24;

        return true;
    }

    bool MemMap::get(size_t loc, uint64_t &val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        // Check if all bytes fit in the entry
        for (int i = 1; i < 8; i++)
            if (entry != this->findEntry(loc + i))
                return false;

        val = (uint64_t)entry->get(entry->toRelative(loc));
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 1))) << 8;
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 2))) << 16;
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 3))) << 24;
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 4))) << 32;
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 5))) << 40;
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 6))) << 48;
        val |= ((uint64_t)entry->get(entry->toRelative(loc + 7))) << 56;

        return true;
    }

    bool MemMap::set(size_t loc, uint8_t val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        entry->set(entry->toRelative(loc), val);

        return true;
    }

    bool MemMap::set(size_t loc, uint16_t val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        // Check if all bytes fit in the entry
        for (int i = 1; i < 2; i++)
            if (entry != this->findEntry(loc + i))
                return false;

        entry->set(entry->toRelative(loc), val & 0xff);
        entry->set(entry->toRelative(loc + 1), (val >> 1) & 0xff);

        return true;
    }

    bool MemMap::set(size_t loc, uint32_t val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        // Check if all bytes fit in the entry
        for (int i = 1; i < 4; i++)
            if (entry != this->findEntry(loc + i))
                return false;

        entry->set(entry->toRelative(loc), val & 0xff);
        entry->set(entry->toRelative(loc + 1), (val >> 1) & 0xff);
        entry->set(entry->toRelative(loc + 2), (val >> 2) & 0xff);
        entry->set(entry->toRelative(loc + 3), (val >> 3) & 0xff);

        return true;
    }

    bool MemMap::set(size_t loc, uint64_t val)
    {
        std::shared_ptr<MemMapEntry> entry = this->findEntry(loc);

        // Check if entry exists
        if (entry == NULL)
            return false;

        // Check if all bytes fit in the entry
        for (int i = 1; i < 8; i++)
            if (entry != this->findEntry(loc + i))
                return false;

        entry->set(entry->toRelative(loc), val & 0xff);
        entry->set(entry->toRelative(loc + 1), (val >> 1) & 0xff);
        entry->set(entry->toRelative(loc + 2), (val >> 2) & 0xff);
        entry->set(entry->toRelative(loc + 3), (val >> 3) & 0xff);
        entry->set(entry->toRelative(loc + 4), (val >> 4) & 0xff);
        entry->set(entry->toRelative(loc + 5), (val >> 5) & 0xff);
        entry->set(entry->toRelative(loc + 6), (val >> 6) & 0xff);
        entry->set(entry->toRelative(loc + 7), (val >> 7) & 0xff);

        return true;
    }

}