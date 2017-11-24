#include "aspka_view.h"

#include <iostream>

namespace aspka {
   
using std::cout;

AspkaView::AspkaView(shared_ptr<AspkaModel> model) 
: model_(model)
{
   std::cout << "view\n";
}

void AspkaView::showInstruments() {
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

} // namespace aspka