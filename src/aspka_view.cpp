#include "aspka_view.h"

#include <iostream>

namespace aspka {

   AspkaView::AspkaView(shared_ptr<AspkaModel> model) 
   : model_(model)
   {
      std::cout << "view\n";
   }

} // namespace aspka