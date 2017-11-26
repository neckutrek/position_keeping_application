#include "model.h"
#include "exception.h"

#include <string>
#include <stdexcept>

namespace aspka {

using std::make_shared;
using std::out_of_range;
using std::to_string;

Model::Model() 
: n_portfolios_(0), n_aquirers_(0), n_counterparties_(0), n_marketplaces_(0), 
  n_instruments_(0), n_trades_(0), n_positions_(0), n_agg_positions_(0)
{
   addInstrument("ABB", "SEK", "Asea Brown Boveri");
   addInstrument("ERIC B", "SEK", "LM Ericsson B");
   addInstrument("HOLM A", "SEK", "Holmen A");
   addInstrument("FING B", "SEK", "Fingerprint Cards B");

   addTrade("ABB", "Stock Portf.", "Equity", "Deutche", "OMX", 14.95, 12, true);
   addTrade("ABB", "Stock Portf.2", "Equity", "Deutche", "OMX", 14.95, 12, true);
   addTrade("ABB", "Stock Portf.2", "Equity", "Deutche", "OMX", 9.95, 5, true);
   addTrade("ERIC B", "Stock Portf.", "Equity", "Deutche", "OMX", 9.55, 15, true);
   addTrade("ERIC B", "Stock Portf.2", "Equity", "Banque Francais", "OMX", 9.55, 15, true);
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
   int instrument_id = findIdFromInstrumentName(name);
   if (instrument_id < 0) {
      throw Exception("The instrument '" + name + "' was not found!\n");
   }

   int portfolio_id = getIntStringMapId(portfolios_, portfolio);
   if (portfolio_id < 0) {
      portfolio_id = n_portfolios_;
      portfolios_.emplace(portfolio_id, portfolio);
      ++n_portfolios_;
   }

   int aquirer_id = getIntStringMapId(aquirers_, aquirer);
   if (aquirer_id < 0) {
      aquirer_id = n_aquirers_;
      aquirers_.emplace(aquirer_id, aquirer);
      ++n_aquirers_;
   }

   int counterparty_id = getIntStringMapId(counterparties_, counterparty);
   if (counterparty_id < 0) {
      counterparty_id = n_counterparties_;
      counterparties_.emplace(counterparty_id, counterparty);
      ++n_counterparties_;
   }

   int marketplace_id = getIntStringMapId(marketplaces_, marketplace);
   if (marketplace_id < 0) {
      marketplace_id = n_marketplaces_;
      marketplaces_.emplace(marketplace_id, marketplace);
      ++n_marketplaces_;
   }

   shared_ptr<Trade> trade = make_shared<Trade>(
      instrument_id, portfolio_id, aquirer_id, counterparty_id, marketplace_id, 
      price, quantity, buy);
   trade_map_.emplace(n_trades_, trade);
   ++n_trades_;

   updatePosition(trade);
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

const string& Model::getPortfolioName
(int id)
{
   try { return portfolios_.at(id); } 
   catch (out_of_range& e) {
      throw Exception("ERROR: No portfolio with id '" + to_string(id) + "'!");
   }
}

const string& Model::getAquirerName
(int id)
{
   try { return aquirers_.at(id); } 
   catch (out_of_range& e) {
      throw Exception("ERROR: No aquirer with id '" + to_string(id) + "'!");
   }
}

const string& Model::getCounterpartyName
(int id)
{
   try { return counterparties_.at(id); } 
   catch (out_of_range& e) {
      throw Exception("ERROR: No counterparty with id '" + to_string(id) + "'!");
   }
}

const string& Model::getMarketplaceName
(int id)
{
   try { return marketplaces_.at(id); } 
   catch (out_of_range& e) {
      throw Exception("ERROR: No marketplace with id '" + to_string(id) + "'!");
   }
}

void Model::applyLambdaOnAllPositions
(const function<void(const Position&)>& fun)
{
   PositionMap::const_iterator it = position_map_.cbegin();
   while (it != position_map_.cend()) {
      if (it->second != nullptr) {
         fun(*(it->second));
      }
      ++it;
   }
}

void Model::applyLambdaOnAggregatePositions
(const function<void(const Position&, int, AggregateType)>& fun, AggregateType agg)
{
   switch (agg) {
   case PORTFOLIO: {
      PositionGroup::const_iterator it = portfolio_group_.cbegin();
      while (it != portfolio_group_.end()) {
         shared_ptr<Position> pos = aggregate_positions_.at(*it);
         fun(*pos, pos->portfolio_id_, agg);
         ++it;
      }
      break;
   }

   case AQUIRER: {
      PositionGroup::const_iterator it = aquirer_group_.cbegin();
      while (it != aquirer_group_.end()) {
         shared_ptr<Position> pos = aggregate_positions_.at(*it);
         fun(*pos, pos->aquirer_id_, agg);
         ++it;
      }
      break;
   }

   case COUNTERPARTY: {
      PositionGroup::const_iterator it = counterparty_group_.cbegin();
      while (it != counterparty_group_.end()) {
         shared_ptr<Position> pos = aggregate_positions_.at(*it);
         fun(*pos, pos->counterparty_id_, agg);
         ++it;
      }
      break;
   }

   case MARKETPLACE: {
      PositionGroup::const_iterator it = marketplace_group_.cbegin();
      while (it != marketplace_group_.end()) {
         shared_ptr<Position> pos = aggregate_positions_.at(*it);
         fun(*pos, pos->marketplace_id_, agg);
         ++it;
      }
      break;
   }
   }
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

int Model::getIntStringMapId
(const IntStringMap& map, const string& name)
{
   int retval = -1;
   IntStringMap::const_iterator it = map.cbegin();
   while (retval < 0 && it != map.cend()) {
      if (it->second.compare(name) == 0) {
         retval = it->first;
      }
      ++it;
   }
   return retval;
}

int Model::getPositionHashKey
(int instrument_id, int portfolio_id_, int aquirer_id, int counterparty_id, 
 int marketplace_id)
{
   // only place for 42 different marketplaces on 32-bit systems
   return instrument_id +
          100*portfolio_id_ +
          10000*aquirer_id +
          1000000*counterparty_id +
          100000000*marketplace_id; 
}

void Model::updatePosition
(shared_ptr<Trade> trade)
{
   int hash_key = getPositionHashKey(
      trade->instrument_id_, trade->portfolio_id_, trade->aquirer_id_, 
      trade->counterparty_id_, trade->marketplace_id_);

   shared_ptr<Position> position = nullptr;
   PositionMap::iterator it = position_map_.find(hash_key);
   if (it == position_map_.end()) {
      position = make_shared<Position>(
         trade->instrument_id_, trade->portfolio_id_, trade->aquirer_id_, 
         trade->counterparty_id_, trade->marketplace_id_, trade->quantity_);
      position_map_.emplace(hash_key, position);
      ++n_positions_;
   }
   else {
      position = it->second;
      if (trade->buy_) {
         position->quantity_ += trade->quantity_;
      }
      else {
         position->quantity_ -= trade->quantity_;
      }
   }

   if (position != nullptr) {
      updateAggregatePositions(hash_key, position, trade);
   }
}

void Model::updateAggregatePositions
(int hash_key, shared_ptr<Position> position, shared_ptr<Trade> trade)
{
   auto update = [this, position, trade](int key, AggregateType agg){
      PositionMap::iterator it = aggregate_positions_.find(key);
      if (it == aggregate_positions_.end()) {
         switch (agg) {
         case PORTFOLIO: {
            aggregate_positions_.emplace(key, make_shared<Position>(
               position->instrument_id_, position->portfolio_id_, -1, -1, -1, 
               position->quantity_, position->market_price_, position->price_trend_));

            PositionGroup::iterator it2 = portfolio_group_.begin();
            bool found = false;
            while (it2 != portfolio_group_.end() && !found) {
               if (aggregate_positions_.at(*it2)->portfolio_id_ > position->portfolio_id_) {
                  found = true;
               }
               else {
                  ++it2;
               }
            }
            portfolio_group_.insert(it2, key);
            break;
         }

         case AQUIRER: {
            aggregate_positions_.emplace(key, make_shared<Position>(
               position->instrument_id_, -1, position->aquirer_id_, -1, -1, 
               position->quantity_, position->market_price_, position->price_trend_));

            PositionGroup::iterator it2 = aquirer_group_.begin();
            bool found = false;
            while (it2 != aquirer_group_.end() && !found) {
               if (aggregate_positions_.at(*it2)->aquirer_id_ > position->aquirer_id_) {
                  found = true;
               }
               else {
                  ++it2;
               }
            }
            aquirer_group_.insert(it2, key);
            break;
         }

         case COUNTERPARTY: {
            aggregate_positions_.emplace(key, make_shared<Position>(
               position->instrument_id_, -1, -1, position->counterparty_id_, -1,
               position->quantity_, position->market_price_, position->price_trend_));

            PositionGroup::iterator it2 = counterparty_group_.begin();
            bool found = false;
            while (it2 != counterparty_group_.end() && !found) {
               if (aggregate_positions_.at(*it2)->counterparty_id_ > position->counterparty_id_) {
                  found = true;
               }
               else {
                  ++it2;
               }
            }
            counterparty_group_.insert(it2, key);
            break;
         }

         case MARKETPLACE: {
            aggregate_positions_.emplace(key, make_shared<Position>(
               position->instrument_id_, -1, -1, -1, position->marketplace_id_,
               position->quantity_, position->market_price_, position->price_trend_));

            PositionGroup::iterator it2 = marketplace_group_.begin();
            bool found = false;
            while (it2 != marketplace_group_.end() && !found) {
               if (aggregate_positions_.at(*it2)->marketplace_id_ > position->marketplace_id_) {
                  found = true;
               }
               else {
                  ++it2;
               }
            }
            marketplace_group_.insert(it2, key);
            break;
         }
         }

         ++n_agg_positions_;
      }
      else {
         shared_ptr<Position> agg_pos = it->second;
         if (agg_pos != nullptr) {
            if (trade->buy_) agg_pos->quantity_ += trade->quantity_;
            else             agg_pos->quantity_ -= trade->quantity_;
         }
      }
   };

   int portfolio_hash = getPositionHashKey(
      position->instrument_id_, position->portfolio_id_, -1, -1, -1);

   int aquirer_hash = getPositionHashKey(
      position->instrument_id_, -1, position->aquirer_id_, -1, -1);

   int counterparty_hash = getPositionHashKey(
      position->instrument_id_, -1, -1, position->counterparty_id_, -1);

   int marketplace_hash = getPositionHashKey(
      position->instrument_id_, -1, -1, -1, position->marketplace_id_);

   update(portfolio_hash, PORTFOLIO);
   update(aquirer_hash, AQUIRER);
   update(counterparty_hash, COUNTERPARTY);
   update(marketplace_hash, MARKETPLACE);
}

} // namespace aspka



