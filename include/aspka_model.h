#ifndef ASPKA_MODEL_H
#define ASPKA_MODEL_H

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
      /*
      Trade(int id, const string& portfolio = "", double price = .0,
            int quantity = 0, bool buy = true,
            const string& aquirer = "", 
      )
      : instrument_id_(id), portfolio(""), price_(.0)
        quantity_(0), trade_time(clock::now()), buy_(true),
        aquirer_(""), counterparty(""), marketplace_("")
      {}
      */
      
      int          instrument_id_;
      string       portfolio_;
      double       price_;
      int quantity_;
      time_point   trade_time_;
      bool         buy_;
      string       aquirer_;
      string       counterparty_;
      string       marketplace_;
   };
   
   /** @brief 
    */
   class AspkaModel {
   public:
      AspkaModel();
      ~AspkaModel() = default;
      
      void                   addInstrument   (const string& name,
                                              const string& currency,
                                              const string& issuer);
      
      inline int             getNInstruments () { return n_instruments_; }
      
      shared_ptr<Instrument> getInstrument   (int id);
      void                   getAllInstrumentNames(string& names);
      
      void                   addTrade();

   private:
      AspkaModel(const AspkaModel&) = delete;
      AspkaModel(AspkaModel&&) = delete;
      AspkaModel& operator=(const AspkaModel&) = delete;
      AspkaModel& operator=(AspkaModel&&) = delete;
     
      using InstrumentMap = unordered_map<int, shared_ptr<Instrument> >;
      InstrumentMap instrument_map_;
      int n_instruments_;
   };
   
} // namespace aspka

#endif //include guard