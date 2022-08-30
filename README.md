# memmulator
This is a memory emulation module for the mulator emulator systems. It features a simple memory interface with ability to create custom memory interfaces by adding entries inheriting from the ```MemMapEntry``` interface class.

## Usage example
```
#include <iostream>
#include <string>

#include <mem.hpp>
#include <memMap.hpp>

using namespace mulator::mem;

// Define 64K of RAM
#define MAX_MEM 1024 * 64

// Create a custom MemMapEntry
class MyMem : public MemMapEntry
{
private:
  uint8_t mem[MAX_MEM];

public:
  MyMem(size_t start = 0)
  {
    this->start = start;
    end = MAX_MEM;
  }

  uint8_t get(size_t relativeLoc)
  {
    return mem[relativeLoc];
  }

  void set(size_t relativeLoc, uint8_t val)
  {
    mem[relativeLoc] = val;
  }

  std::string getName()
  {
    return "RAM";
  }
};

int main()
{
  // Create memMap object
  MemMap memMap;

  // Add entry
  memMap.addEntry<MyMem>(12);
  //                     ^^---arguments in here will be passed to the constructor of your MyMem

  // This will print all entries added to the memory map
  std::cout << memMap.dumpEntries();
  /*

  Output:
    ==== Entry dump ====
    Name:  RAM
    Start: 12
    End:   65536
    --------------------

  */
}
```