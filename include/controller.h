#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

#include <string>
#include <memory>

namespace aspka {

   using std::string;
   using std::shared_ptr;
   
   /** @brief 
    */
   class Controller {
   public:
      Controller(shared_ptr<Model>);
      ~Controller() = default;

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
      Controller(const Controller&) = delete;
      Controller(Controller&&) = delete;
      Controller& operator=(const Controller&) = delete;
      Controller& operator=(Controller&&) = delete;
     
      shared_ptr<Model> model_;

   };

} // namespace aspka

#endif //include guard
