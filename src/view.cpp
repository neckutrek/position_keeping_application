#include "view.h"

#include <iostream>
#include <iomanip>

namespace aspka {
   
using std::cout;
using std::setw;
using std::to_string;

View::View(shared_ptr<Model> model) 
: model_(model)
{}

void View::showInstruments() {
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| REGISTERED FINANCIAL INSTRUMENTS                                             |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| Name     | Currency | Market Price | Issuer                                  |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   
   auto printInfo = [](const string& name,
                       const string& currency,
                       double price,
                       const string& issuer) 
   {
      string price_str = to_string(price);
      price_str = price_str.substr(0, price_str.length()-4);
      cout << "| " << setw(8) << name 
           << " | " << setw(8) << currency 
           << " | " << setw(12) << price_str
           << " | " << setw(39) << std::left << issuer.substr(0, 39)
           << std::right << " |\n";
   };
   
   int n_instruments = model_->getNInstruments();
   shared_ptr<Instrument> p;
   for (int i=0; i<n_instruments; ++i) {
      p = model_->getInstrument(i);
      if (p != nullptr) {
         printInfo(p->name_, p->currency_, p->market_price_, p->issuer_);
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

void View::showPositions()
{
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| ALL CURRENT POSITIONS                                                        |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| Instrument | Portfolio     | Aquirer       | Counterparty   | Marketplace    |\n";
   cout << "|            | Market Price  | Position      |                |                |\n";
   cout << "|------------------------------------------------------------------------------|\n";

   auto printPosition = [this](const Position& pos){
      shared_ptr<Instrument> instrument = model_->getInstrument(pos.instrument_id_);
      cout << "| " 
           << setw(10) << instrument->name_ << " | "
           << setw(13) << model_->getPortfolioName(pos.portfolio_id_) << " | "
           << setw(13) << model_->getAquirerName(pos.aquirer_id_) << " | "
           << setw(14) << model_->getCounterpartyName(pos.counterparty_id_) << " | "
           << setw(14) << model_->getMarketplaceName(pos.marketplace_id_) << " |\n";

      string price = to_string(instrument->market_price_);
      price = price.substr(0, price.length()-4);
      cout << "|            | "
           << setw(13) << price << " | "
           << setw(13) << pos.quantity_ 
           << " |                |                |\n";
      cout << "|------------------------------------------------------------------------------|\n";
   };

   model_->applyLambdaOnAllPositions(printPosition);
}

void View::showAggregatedPositions()
{
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "| CURRENT POSITIONS   (Grouped on 'Portfolio').                                |\n";
   cout << "|------------------------------------------------------------------------------|\n";
   cout << "|   Instrument | Market Price | Curr | Pos | Market Value | Tot. Traded Amount |\n";
   cout << "|------------------------------------------------------------------------------|\n";

   int group_value = -1;

   auto printPosition = [this, &group_value](const Position& pos, 
                                             int new_group_value, 
                                             AggregateType agg)
   {
      if (new_group_value > group_value) {
         group_value = new_group_value;
         switch (agg) {
         case PORTFOLIO: {
            cout << "| " << std::left << setw(76) 
                 << model_->getPortfolioName(pos.portfolio_id_)
                 << " |\n";
            break;
         }

         case AQUIRER: {
            cout << "| " << std::left << setw(76) 
                 << model_->getAquirerName(pos.aquirer_id_)
                 << " |\n";
            break;
         }

         case COUNTERPARTY : {
            cout << "| " << std::left << setw(76) 
                 << model_->getCounterpartyName(pos.counterparty_id_)
                 << " |\n";
            break;
         }

         case MARKETPLACE: {
            cout << "| " << std::left << setw(76) 
                 << model_->getMarketplaceName(pos.marketplace_id_)
                 << " |\n";
            break;
         }
         }
      }

      shared_ptr<Instrument> instrument = 
         model_->getInstrument(pos.instrument_id_);

      string price = to_string(instrument->market_price_);
      price = price.substr(0, price.length()-4);

      string value = to_string(instrument->market_price_ * pos.quantity_);
      value = value.substr(0, value.length()-4);

      cout << "| " << std::right
           << setw(12) << instrument->name_ << " | "
           << setw(12) << price << " | "
           << setw(4)  << instrument->currency_ << " | "
           << setw(3)  << pos.quantity_ << " | "
           << setw(12) << value << " | "
           << setw(18) << pos.total_traded_amount_ <<" |\n";
   };

   model_->applyLambdaOnAggregatePositions(printPosition, current_grouping_);
   cout << "|------------------------------------------------------------------------------|\n";
}

} // namespace aspka





