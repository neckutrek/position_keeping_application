#ifndef ASPKA_VIEW_H
#define ASPKA_VIEW_H

#include "aspka_model.h"

#include <memory>

namespace aspka {
   
   using std::shared_ptr;

   /** @brief 
    */
   class AspkaView {
   public:
      AspkaView(shared_ptr<AspkaModel>);
      ~AspkaView() = default;

   private:
      AspkaView(const AspkaView&) = delete;
      AspkaView(AspkaView&&) = delete;
      AspkaView& operator=(const AspkaView&) = delete;
      AspkaView& operator=(AspkaView&&) = delete;
     
      shared_ptr<AspkaModel> model_;

   };

} // namespace aspka

#endif //include guard