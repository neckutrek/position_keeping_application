#include "aspka_controller.h"

#include <iostream>

namespace aspka {

   AspkaController::AspkaController(shared_ptr<AspkaModel> model) 
   : model_(model)
   {
      std::cout << "controller\n";
   }

} // namespace aspka