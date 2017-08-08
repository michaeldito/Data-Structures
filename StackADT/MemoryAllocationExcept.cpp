#include "MemoryAllocationExcept.hpp"

MemoryAllocationExcept::MemoryAllocationExcept(const std::string& message):
  std::bad_alloc("Precondition Violated Exception: " + message) {}
