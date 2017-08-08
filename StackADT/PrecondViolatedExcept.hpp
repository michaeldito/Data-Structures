#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public std::logic_error {
 public:
   PrecondViolatedExcept(const std::string& message = "");
};

#endif
