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

   private:
      View(const View&) = delete;
      View(View&&) = delete;
      View& operator=(const View&) = delete;
      View& operator=(View&&) = delete;
     
      shared_ptr<Model> model_;

   };

} // namespace aspka

#endif //include guard