#include "aspka_app.h"

#include <iostream>

namespace aspka {

   using std::cin;
   using std::cout;

   AspkaApp::AspkaApp(int argc, char** argv) 
   : cmds_map_{
      {"help",                [this](){ displayHelp(); } },
      {"register instrument", [this](){ registerInstrument(); } },
      {"register trade",      [this](){ registerTrade(); } },
      {"show instrument",     [this](){ showInstruments(); } },
      {"show trades",         [this](){ showTrades(); } },
      {"show positions",      [this](){ showPositions(); } },
      {"set grouping",        [this](){ setGrouping(); } },
      {"view_positions",      [this](){ viewPositions(); } } }
   {

   }

   int AspkaApp::run() {
      cout << "ASPKA - A Small Position Keeping Application\n";
      cout << "Welcome to ASPKA v. 0.1\n";
      cout << "Written by: Marcus Johansson, Nov-2017\n";

      
      string user_input("");
      bool quit = false;
      while (!quit) {
         cout << "\n> ";
         getline(cin, user_input);
         if (user_input.compare("quit") == 0) {
            quit = true;
            break;
         }

         CmdMap::iterator it = cmds_map_.find(user_input);
         if (it != cmds_map_.end()) {
            it->second(); // call the lambda inside second
         }
         else {
            cout << "The command was not understood. Try 'help'!\n";
         }

         
      }
      

      return 0;
   }

   void AspkaApp::displayHelp() {
      cout << "Command   Argument       Description\n";
      //cout << "\n";
      cout << "help                     Displays this help information.\n";
      //cout << "\n";
      cout << "register  instrument     Registers a new financial instrument.\n";
      //cout << "\n";
      cout << "          trade          Registers a trade of an instrument.\n";
      //cout << "\n";
      cout << "show      instrument     Shows all registered financial instruments.\n";
      //cout << "\n";
      cout << "          trades         Shows all track records.\n";
      //cout << "\n";
      cout << "          positions      Shows all currently open positions grouped.\n";
      //cout << "\n";
      cout << "set       grouping       Sets which grouping to use for displaying positions.\n";
      //cout << "\n";
      cout << "quit                     Quits this program.\n";
      //cout << "\n";
      cout << "- - -\n";
      //cout << "\n";
      cout << "view_positions           Shows all currently open positions. (FOR DEBUGGING)\n";
   }

   void AspkaApp::registerInstrument() {
      cout << "register instrument!\n";
   }

   void AspkaApp::registerTrade() {
      cout << "register trade!\n";
   }

   void AspkaApp::showInstruments() {
      cout << "show instruments!!\n";
   }

   void AspkaApp::showTrades() {
      cout << "showTrades!\n";
   }

   void AspkaApp::showPositions() {
      cout << "showPositions!\n";
   }

   void AspkaApp::setGrouping() {
      cout << "set grouping!\n";
   }

   void AspkaApp::viewPositions() {
      cout << "view positions!\n";
   }

}


