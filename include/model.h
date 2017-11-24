#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <unordered_map>
#include <memory>
#include <chrono>

namespace aspka {
   
   using std::string;
   using std::unordered_map;
   using std::shared_ptr;
   using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
   using clock = std::chrono::high_resolution_clock;
   
   /** @brief 
    */
   class Instrument {
   public:
      Instrument(const string& name, const string& currency, const string& issuer)
      : name_(name), currency_(currency), issuer_(issuer) 
      {}
      
      string name_;
      string currency_;
      string issuer_;
   };
   
   /** @brief 
    */
   class Trade {
   public:
      Trade(int id, const string& portfolio, const string& aquirer, 
            const string& counterparty, const string& marketplace, 
            double price, int quantity, bool buy)
      : instrument_id_(id), portfolio_(portfolio), aquirer_(aquirer), 
        counterparty_(counterparty), marketplace_(marketplace), price_(price),
        quantity_(quantity), buy_(buy), trade_time_(clock::now())
      {}
      
      int          instrument_id_;
      string       portfolio_;
      string       aquirer_;
      string       counterparty_;
      string       marketplace_;
      double       price_;
      int          quantity_;
      bool         buy_;
      time_point   trade_time_;
   };
   
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
      
   private:
      Model(const Model&) = delete;
      Model(Model&&) = delete;
      Model& operator=(const Model&) = delete;
      Model& operator=(Model&&) = delete;
      
      using InstrumentMap = unordered_map<int, shared_ptr<Instrument> >;
      InstrumentMap instrument_map_;
      int n_instruments_;
      int findIdFromInstrumentName(const string& name);

      using TradeMap = unordered_map<int, shared_ptr<Trade> >;
      TradeMap trade_map_;
      int n_trades_;
   };
   
} // namespace aspka

#endif //include guard