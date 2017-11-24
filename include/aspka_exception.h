#ifndef ASPKA_EXCEPTION_H
#define ASPKA_EXCEPTION_H

#include <exception>
#include <string>

namespace aspka {

   using std::runtime_error;
   using std::string;

   class AspkaException : public runtime_error {
   public:
      explicit AspkaException(const string& msg)
      : runtime_error(msg) {}
   };

} // namespace aspka

#endif // include guard