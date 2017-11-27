#include "market_simulator.h"

#include <iostream>

namespace aspka {

MarketSimulator::MarketSimulator
(shared_ptr<Model> model)
: model_(model), 
  market_simulator_thread_(&MarketSimulator::run, this)
{

}

void MarketSimulator::start() 
{
   //market_simulator_thread_.detach(); 
}

void MarketSimulator::run()
{
   while (true) {
      std::cout << "hej\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }
}

} // namespace aspka