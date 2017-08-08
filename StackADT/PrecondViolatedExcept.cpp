#include "PrecondViolatedExcept.hpp"

PrecondViolatedExcept::PrecondViolatedExcept(const std::string& message):
  std::logic_error("Precondition Violated Exception: " + message) {}
