#include "aspka_controller.h"

#include <iostream>

namespace aspka {

AspkaController::AspkaController
(shared_ptr<AspkaModel> model) 
: model_(model)
{
   
}

void AspkaController::registerInstrument
(const string& name, const string& currency, const string& issuer) 
{
   model_->addInstrument(name, currency, issuer);
}

void AspkaController::registerTrade
(const string& name, const string& portfolio,  const string& aquirer, 
 const string& counterparty, const string& marketplace, double price, 
 int quantity, bool buy)
{
   std::cout << "adding trade\n";
}

} // namespace aspka