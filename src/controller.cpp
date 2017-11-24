#include "controller.h"

#include <iostream>

namespace aspka {

Controller::Controller
(shared_ptr<Model> model) 
: model_(model)
{
   
}

void Controller::registerInstrument
(const string& name, const string& currency, const string& issuer) 
{
   model_->addInstrument(name, currency, issuer);
}

void Controller::registerTrade
(const string& name, const string& portfolio,  const string& aquirer, 
 const string& counterparty, const string& marketplace, double price, 
 int quantity, bool buy)
{
   model_->addTrade(name, portfolio, aquirer, counterparty, marketplace,
                    price, quantity, buy);


}

} // namespace aspka