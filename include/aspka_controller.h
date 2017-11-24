#ifndef ASPKA_CONTROLLER_H
#define ASPKA_CONTROLLER_H

#include "aspka_model.h"

#include <string>
#include <memory>

namespace aspka {

   using std::string;
   using std::shared_ptr;
   
   /** @brief 
    */
   class AspkaController {
   public:
      AspkaController(shared_ptr<AspkaModel>);
      ~AspkaController() = default;

      void registerInstrument(const string& name,
                              const string& currency,
                              const string& issuer);
      
      void registerTrade(const string& name,
                         const string& portfolio, 
                         const string& aquirer, 
                         const string& counterparty,
                         const string& marketplace, 
                         double price, 
                         int quantity, 
                         bool buy);

   private:
      AspkaController(const AspkaController&) = delete;
      AspkaController(AspkaController&&) = delete;
      AspkaController& operator=(const AspkaController&) = delete;
      AspkaController& operator=(AspkaController&&) = delete;
     
      shared_ptr<AspkaModel> model_;

   };

} // namespace aspka

#endif //include guard
