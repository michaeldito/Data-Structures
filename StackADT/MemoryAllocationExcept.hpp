#ifndef MEMORY_ALLOCATION_EXCEPT_
#define MEMORY_ALLOCATION_EXCEPT_

#include <stdexcept>
#include <string>

class MemoryAllocationExcept : public std::bad_alloc {
 public:
   MemoryAllocationExcept(const std::string& message = "");
};

#endif
