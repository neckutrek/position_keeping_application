#include "aspka_model.h"
#include "aspka_exception.h"

namespace aspka {
   
using std::make_shared;

AspkaModel::AspkaModel() 
: n_instruments_(0)
{
   addInstrument("ABB", "SEK", "Asea Brown Boveri");
   addInstrument("LME", "SEK", "LM Ericsson");
}

void AspkaModel::addInstrument
(const string& name, const string& currency, const string& issuer)
{
   InstrumentMap::iterator it = instrument_map_.begin();
   while (it != instrument_map_.end()) {
      if (name.compare(it->second->name_) == 0) {
         throw AspkaException("An instrument with name '" + name + "' already exists!");
      }
      ++it;
   }
   
   instrument_map_.emplace(n_instruments_, make_shared<Instrument>(name, currency, issuer));
   ++n_instruments_;
}

shared_ptr<Instrument> AspkaModel::getInstrument
(int id)
{
   InstrumentMap::iterator it = instrument_map_.find(id);
   if (it != instrument_map_.end()) {
      return it->second;
   }
   return nullptr;
}

void AspkaModel::getAllInstrumentNames
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

void AspkaModel::addTrade()
{
   
}

} // namespace aspka