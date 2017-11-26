#ifndef VIEW_H
#define VIEW_H

#include "model.h"

#include <memory>

namespace aspka {
   
   using std::shared_ptr;

   /** @brief 
    */
   class View {
   public:
      View(shared_ptr<Model>);
      ~View() = default;
      
      void showInstruments();

      void showTrades();

      void showPositions();

      void showAggregatedPositions();

      inline void setGrouping(AggregateType agg) 
      { current_grouping_ = agg; }

   private:
      View(const View&) = delete;
      View(View&&) = delete;
      View& operator=(const View&) = delete;
      View& operator=(View&&) = delete;
     
      shared_ptr<Model> model_;

      AggregateType current_grouping_;
   };

} // namespace aspka

#endif //include guard