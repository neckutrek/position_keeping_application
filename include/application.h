#ifndef APPLICATION_H
#define APPLICATION_H

#include "model.h"
#include "view.h"
#include "controller.h"
#include "market_simulator.h"

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace aspka {

   using std::map;
   using std::string;
   using std::vector;
   using std::function;
   using std::unique_ptr;
   using std::shared_ptr;

   /** @brief 
    */
   class Application {
   public:
      explicit Application(int argc, char** argv);
      ~Application() = default;

      int run();

   private:
      Application(const Application&) = delete;
      Application(Application&&) = delete;
      Application& operator=(const Application&) = delete;
      Application& operator=(Application&&) = delete;

      void displayHelp();
      void registerInstrument();
      void registerTrade();
      void showInstruments();
      void showTrades();
      void showPositions();
      void setGrouping();
      void viewPositions();

      using CmdMap = map<string, function<void()> >;
      CmdMap                       cmds_map_;

      shared_ptr<Model>       model_;
      unique_ptr<View>        view_;
      unique_ptr<Controller>  controller_;

      vector<string>          arguments_;

      MarketSimulator         market_simulator_;

   };

} // namespace aspka

#endif // include guard