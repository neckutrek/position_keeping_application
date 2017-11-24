#include "model.h"
#include "exception.h"

namespace aspka {
   
using std::make_shared;

Model::Model() 
: n_instruments_(0), n_trades_(0)
{
   addInstrument("ABB", "SEK", "Asea Brown Boveri");
   addInstrument("LME", "SEK", "LM Ericsson");

   addTrade("ABB", "Stock Portfolio", "Equity", "Deutche", "OMX", 14.95, 12, true);
   addTrade("LME", "Stock Portfolio", "Equity", "Deutche", "OMX", 9.55, 15, true);
}

void Model::addInstrument
(const string& name, const string& currency, const string& issuer)
{
   InstrumentMap::iterator it = instrument_map_.begin();
   while (it != instrument_map_.end()) {
      if (name.compare(it->second->name_) == 0) {
         throw Exception("An instrument with name '" + name + "' already exists!");
      }
      ++it;
   }
   
   instrument_map_.emplace(n_instruments_, make_shared<Instrument>(name, currency, issuer));
   ++n_instruments_;
}

shared_ptr<Instrument> Model::getInstrument
(int id)
{
   InstrumentMap::iterator it = instrument_map_.find(id);
   if (it != instrument_map_.end()) {
      return it->second;
   }
   return nullptr;
}

void Model::getAllInstrumentNames
(string& names)
{
   names = "";
   InstrumentMap::iterator it = instrument_map_.begin();
   while (it != instrument_map_.end()) {
      if (it->second != nullptr) {
         names += it->second->name_ + ", ";
      }
      ++it;
   }
   if (names.compare("") != 0) {
      names = names.substr(0, names.length()-2);
   }
}

void Model::addTrade
(const string& name, const string& portfolio, const string& aquirer, 
 const string& counterparty, const string& marketplace, double price, 
 int quantity, bool buy)
{
   int id = findIdFromInstrumentName(name);
   if (id < 0) {
      throw Exception("The instrument '" + name + "' was not found!\n");
   }

   trade_map_.emplace(n_trades_, make_shared<Trade>(
      id, portfolio, aquirer, counterparty, marketplace, price, quantity, buy
   ));
   ++n_trades_;
}

shared_ptr<Trade> Model::getTrade
(int id)
{
   TradeMap::iterator it = trade_map_.find(id);
   if (it != trade_map_.end()) {
      return it->second;
   }
   return nullptr;
}






int Model::findIdFromInstrumentName
(const string& name)
{
   int retval = -1;
   InstrumentMap::iterator it = instrument_map_.begin();
   while (retval < 0 && it != instrument_map_.end()) {
      if (it->second != nullptr) {
         if (it->second->name_.compare(name) == 0) {
            retval = it->first;
         }
      }
      ++it;
   }
   return retval;
}

} // namespace aspka



