#include "view.h"

#include <iostream>

namespace aspka {
   
using std::cout;

View::View(shared_ptr<Model> model) 
: model_(model)
{
   std::cout << "view\n";
}

void View::showInstruments() {
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| REGISTERED FINANCIAL INSTRUMENTS                                             |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| Name | Currency | Issuer                                                     |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   
   auto printInfo = [](const string& name,
                       const string& currency,
                       const string& issuer) {
      cout << "|  " << name << " |      " << currency << " | ";
      if (issuer.length() > 59) cout << issuer.substr(0, 59);
      else {
         cout << issuer;
         for (unsigned int i=0; i<59-issuer.length(); ++i) {
            cout << " ";
         }
      }
      cout << "|\n";
   };
   
   int n_instruments = model_->getNInstruments();
   shared_ptr<Instrument> p;
   for (int i=0; i<n_instruments; ++i) {
      p = model_->getInstrument(i);
      if (p != nullptr) {
         printInfo(p->name_, p->currency_, p->issuer_);
      }
   }
   
   cout << "|------------------------------------------------------------------------------|\n";
}

void View::showTrades()
{
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| TRACK RECORD                                                                 |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| Instrument | Portfolio       | Price, Quantity  | Trade Time  | Buy/Sell     |\n";
   cout << "|            | Aquirer         | Counterparty     |             | Marketplace  |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   
   /*
   auto printInfo = [](const string& name,
                       const string& currency,
                       const string& issuer) {
      cout << "|  " << name << " |      " << currency << " | ";
      if (issuer.length() > 59) cout << issuer.substr(0, 59);
      else {
         cout << issuer;
         for (unsigned int i=0; i<59-issuer.length(); ++i) {
            cout << " ";
         }
      }
      cout << "|\n";
   };
   */
   
   int n_trades = model_->getNTrades();
   shared_ptr<Trade> p;
   for (int i=0; i<n_trades; ++i) {
      p = model_->getTrade(i);
      if (p != nullptr) {
         cout << p->portfolio_ << "\n";
         cout << "|------------------------------------------------------------------------------|\n";
         //printInfo(p->name_, p->currency_, p->issuer_);
      }
   }
}

} // namespace aspka