#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>

namespace aspka {
   
   using std::string;
   using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
   using clock = std::chrono::high_resolution_clock;
   using std::rand;

   /** @brief 
    */
   class Instrument {
   public:
      Instrument(const string& name, const string& currency, const string& issuer)
      : name_(name), currency_(currency), issuer_(issuer), market_price_(.0)
      {
         market_price_ = static_cast<double>(1000 + rand()%1000) / 100.0;
      }
      
      string name_;
      string currency_;
      string issuer_;
      double market_price_;
   };
   
   /** @brief 
    */
   class Trade {
   public:
      Trade(int instrument_id, int portfolio_id, int aquirer_id, 
            int counterparty_id, int marketplace_id, 
            double price, int quantity, bool buy)
      : instrument_id_(instrument_id), portfolio_id_(portfolio_id), 
        aquirer_id_(aquirer_id), counterparty_id_(counterparty_id), 
        marketplace_id_(marketplace_id), price_(price),
        quantity_(quantity), buy_(buy), trade_time_(clock::now())
      {}
      
      int          instrument_id_;
      int          portfolio_id_;
      int          aquirer_id_;
      int          counterparty_id_;
      int          marketplace_id_;
      double       price_;
      int          quantity_;
      bool         buy_;
      time_point   trade_time_;
   };

   /** @brief
    */
   class Position {
   public:
      Position(int instrument_id, int portfolio_id, int aquirer_id, 
               int counterparty_id, int marketplace_id, int quantity,
               double market_price = .0, double price_trend = .0)
      : instrument_id_(instrument_id), portfolio_id_(portfolio_id), 
        aquirer_id_(aquirer_id), counterparty_id_(counterparty_id), 
        marketplace_id_(marketplace_id), quantity_(quantity),
        total_traded_amount_(quantity)//,
        //market_price_(market_price), price_trend_(price_trend)
      {}

      const int instrument_id_;
      const int portfolio_id_;
      const int aquirer_id_;
      const int counterparty_id_;
      const int marketplace_id_;
      int quantity_;
      int total_traded_amount_;
      //double market_price_;
      //double price_trend_;
   };

   enum AggregateType : int {PORTFOLIO, AQUIRER, COUNTERPARTY, MARKETPLACE};

} // namespace aspka

#endif // include guard