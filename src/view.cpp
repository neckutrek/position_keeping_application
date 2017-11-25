#include "view.h"

#include <iostream>
#include <iomanip>

namespace aspka {
   
using std::cout;
using std::setw;
using std::to_string;

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
   
   int n_trades = model_->getNTrades();
   shared_ptr<Trade> p;
   for (int i=0; i<n_trades; ++i) {
      p = model_->getTrade(i);
      if (p != nullptr) {
         string name = "";
         shared_ptr<Instrument> instrument = model_->getInstrument(p->instrument_id_);
         if (instrument != nullptr) {
            name = instrument->name_;
         }
         string price = to_string(p->price_);
         string pq = price.substr(0, price.length()-4) + ", " + to_string(p->quantity_);
         cout << "| " << setw(10) << name << " | "
              << setw(15) << model_->getPortfolioName(p->portfolio_id_) << " | "
              << setw(16) << pq << " | "
              << "2017-xx-xx " << " | "
              << setw(12) << (p->buy_ ? "Buy" : "Sell") << " |\n";
         cout << "|            | "
              << setw(15) << model_->getAquirerName(p->aquirer_id_) << " | "
              << setw(16) << model_->getCounterpartyName(p->counterparty_id_) << " | "
              << "10:43:22.15" << " | "
              << setw(12) << model_->getMarketplaceName(p->marketplace_id_) << " |\n";
         cout << "|------------------------------------------------------------------------------|\n";
      }
   }
}

} // namespace aspka





