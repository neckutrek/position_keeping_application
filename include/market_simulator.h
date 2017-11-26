#ifndef MARKET_SIMULATOR_H
#define MARKET_SIMULATOR_H

#include "model.h"

#include <thread>
#include <memory>

namespace aspka {
   
   using std::thread;
   using std::shared_ptr;

   class MarketSimulator {
   public:
      MarketSimulator(shared_ptr<Model> model);
      ~MarketSimulator() = default;

      void start();

   private:
      MarketSimulator(const MarketSimulator&) = delete;
      MarketSimulator(MarketSimulator&&) = delete;
      MarketSimulator& operator=(const MarketSimulator&) = delete;
      MarketSimulator& operator=(MarketSimulator&&) = delete;

      void run();

      shared_ptr<Model>       model_;
      thread                  market_simulator_thread_;
   };

} // namespace aspka

#endif // include guard