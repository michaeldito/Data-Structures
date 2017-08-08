#ifndef MEMORY_ALLOCATION_EXCEPT_
#define MEMORY_ALLOCATION_EXCEPT_

#include <stdexcept>
#include <new>
#include <string>

class MemoryAllocationExcept : public std::bad_alloc {
 public:
   MemoryAllocationExcept(): std::bad_alloc() {}
};

#endif
