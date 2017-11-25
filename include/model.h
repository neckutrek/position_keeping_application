#ifndef MODEL_H
#define MODEL_H

#include "primitives.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace aspka {
   
   using std::string;
   using std::unordered_map;
   using std::shared_ptr;
   
   /** @brief 
    */
   class Model {
   public:
      Model();
      ~Model() = default;
      
      void                   addInstrument   (const string& name,
                                              const string& currency,
                                              const string& issuer);
      
      inline int             getNInstruments () { return n_instruments_; }
      
      shared_ptr<Instrument> getInstrument   (int id);

      void                   getAllInstrumentNames(string& names);
      
      void                   addTrade(const string& name,
                                      const string& portfolio, 
                                      const string& aquirer, 
                                      const string& counterparty,
                                      const string& marketplace, 
                                      double price, 
                                      int quantity, 
                                      bool buy);

      inline int             getNTrades () { return n_trades_; }

      shared_ptr<Trade>      getTrade   (int id);

      const string&          getPortfolioName(int id);
      const string&          getAquirerName(int id);
      const string&          getCounterpartyName(int id);
      const string&          getMarketplaceName(int id);
      
   private:
      Model(const Model&) = delete;
      Model(Model&&) = delete;
      Model& operator=(const Model&) = delete;
      Model& operator=(Model&&) = delete;

      using IntStringMap = unordered_map<int, string>;
      IntStringMap         portfolios_;
      int                  n_portfolios_;
      IntStringMap         aquirers_;
      int                  n_aquirers_;
      IntStringMap         counterparties_;
      int                  n_counterparties_;
      IntStringMap         marketplaces_;
      int                  n_marketplaces_;
      int getIntStringMapId(const IntStringMap& map, const string& name);
      
      using InstrumentMap = unordered_map<int, shared_ptr<Instrument> >;
      InstrumentMap instrument_map_;
      int n_instruments_;
      int findIdFromInstrumentName(const string& name);

      using TradeMap = unordered_map<int, shared_ptr<Trade> >;
      TradeMap trade_map_;
      int n_trades_;

      //using PositionMap = unordered_map<int, shared_ptr<Position> >;
      //PositionMap position_map_;
      //int n_positions_;
   };
   
} // namespace aspka

#endif //include guard





