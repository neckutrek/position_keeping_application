#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace aspka {

   using std::runtime_error;
   using std::string;

   class Exception : public runtime_error {
   public:
      explicit Exception(const string& msg)
      : runtime_error(msg) {}
   };

} // namespace aspka

#endif // include guard