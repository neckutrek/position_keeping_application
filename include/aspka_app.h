#ifndef ASPKA_APP_H
#define ASPKA_APP_H

#include "aspka_model.h"
#include "aspka_view.h"
#include "aspka_controller.h"

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
   class AspkaApp {
   public:
      explicit AspkaApp(int argc, char** argv);
      ~AspkaApp() = default;

      int run();

   private:
      AspkaApp(const AspkaApp&) = delete;
      AspkaApp(AspkaApp&&) = delete;
      AspkaApp& operator=(const AspkaApp&) = delete;
      AspkaApp& operator=(AspkaApp&&) = delete;

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

      shared_ptr<AspkaModel>       model_;
      unique_ptr<AspkaView>        view_;
      unique_ptr<AspkaController>  controller_;

      vector<string>               arguments_;

   };

} // namespace aspka

#endif // include guard