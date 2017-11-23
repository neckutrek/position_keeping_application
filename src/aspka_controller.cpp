#include "aspka_controller.h"

#include <iostream>

namespace aspka {

   AspkaController::AspkaController(shared_ptr<AspkaModel> model) 
   : model_(model)
   {
      
   }

   void AspkaController::registerInstrument
   (const string& name, const string& currency, const string& issuer) 
   {
      std::cout << name << ", " << currency << ", " << issuer << "\n";
   }

} // namespace aspka