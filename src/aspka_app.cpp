#include "aspka_app.h"

#include <iostream>
#include "aspka_exception.h"

namespace aspka {

using std::cin;
using std::cout;
using std::make_unique;
using std::make_shared;

AspkaApp::AspkaApp(int argc, char** argv) 
: cmds_map_{
   {"help",                [this](){ displayHelp(); } },
   {"register instrument", [this](){ registerInstrument(); } },
   {"register trade",      [this](){ registerTrade(); } },
   {"show instruments",    [this](){ showInstruments(); } },
   {"show trades",         [this](){ showTrades(); } },
   {"show positions",      [this](){ showPositions(); } },
   {"set grouping",        [this](){ setGrouping(); } },
   {"view_positions",      [this](){ viewPositions(); } } },
   model_(make_shared<AspkaModel>()),
   view_(make_unique<AspkaView>(model_)),
   controller_(make_unique<AspkaController>(model_))
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
         try {
            it->second(); // call the lambda inside second
         } catch (std::bad_function_call& e) {
            cout << "ERROR: The command '" << it->first 
                  << "' is not implemented.\nMsg: '" << e.what() 
                  << "'!\n";
         }
      }
      else {
         cout << "The command was not understood. Try 'help'!\n";
      }
   }

   return 0;
}

void AspkaApp::displayHelp() {
   cout << "Command   Argument       Description\n";
   cout << "help                     Displays this help information.\n";
   cout << "register  instrument     Registers a new financial instrument.\n";
   cout << "          trade          Registers a trade of an instrument.\n";
   cout << "show      instruments    Shows all registered financial instruments.\n";
   cout << "          trades         Shows all track records.\n";
   cout << "          positions      Shows all currently open positions grouped.\n";
   cout << "set       grouping       Sets which grouping to use for displaying positions.\n";
   cout << "quit                     Quits this program.\n";
   cout << "- - -\n";
   cout << "view_positions           Shows all currently open positions. (FOR DEBUGGING)\n";
}

void AspkaApp::registerInstrument() {
   cout << "Registering of a new financial instrument:\n";
   
   cout << "Instrument name: ";
   string name = "";
   getline(cin, name);

   cout << "Currency:        ";
   string currency = "";
   getline(cin, currency);

   cout << "Issuer:          ";
   string issuer = "";
   getline(cin, issuer);

   try {
      controller_->registerInstrument(name, currency, issuer);
      cout << "\nSuccessfully registered new financial instrument!\n";
   } catch (AspkaException& e) {
      cout << e.what() << "\n";
   }
}

void AspkaApp::registerTrade() {
   cout << "Registering of a new trade:\n";
   
   string names = "";
   model_->getAllInstrumentNames(names);
   cout << "(Available instruments: " << names << ")\n";
   cout << "Instrument name: ";
   string name = "";
   getline(cin, name);
   
   cout << "Portfolio:       ";
   string portfolio = "";
   getline(cin, portfolio);
   
   cout << "Aquirer:         ";
   string aquirer = "";
   getline(cin, aquirer);
   
   cout << "Counterparty:    ";
   string counterparty = "";
   getline(cin, counterparty);
   
   cout << "Marketplace:     ";
   string marketplace = "";
   getline(cin, marketplace);
   
   cout << "(type '-' to set to current market price)\n";
   double price = .0;
   bool success = false;
   while (!success) {
      try {
         cout << "Price:           ";
         string price_str = "";
         getline(cin, price_str);
         if (price_str.compare("-") == 0) {
               price = 10.0;
         }
         else {
            price = std::stod(price_str);
         }
         success = true;
      } catch (std::invalid_argument& e) {
         cout << "Invalid input, try again!\n";
      }
   }
   
   int quantity = 0;
   success = false;
   while (!success) {
      try {
         cout << "Quantity:        ";
         string quantity_str = "";
         getline(cin, quantity_str);
         quantity = std::stoi(quantity_str);
         success = true;
      } catch (std::invalid_argument& e) {
         cout << "Invalid input, try again!\n";
      }
   }
   
   bool buy = false;
   success = false;
   while (!success) {
      cout << "Buy/Sell:       ";
      string buy_str = "";
      getline(cin, buy_str);
      if (buy_str.compare("Buy") == 0) {
         buy = true;
         success = true;
      }
      else if (buy_str.compare("Sell") == 0) {
         buy = false;
         success = true;
      }
      else {
         cout << "Invalid input, try again!\n";
      }
   }
   
   try {
      controller_->registerTrade(name, portfolio, aquirer, counterparty, 
                                 marketplace, price, quantity, buy);
      cout << "\nSuccessfully executed trade order!\n";
   } catch (AspkaException& e) {
      cout << e.what() << "\n";
   }
}

void AspkaApp::showInstruments() {
   try {
      view_->showInstruments();
   } catch (AspkaException& e) {
      cout << e.what() << "\n";
   }
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

} // namespace aspka


