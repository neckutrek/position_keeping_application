#ifndef ASPKA_VIEW_H
#define ASPKA_VIEW_H

namespace aspka {
   
   /** @brief 
    */
   class AspkaView {
   public:
      AspkaView() = default;
      ~AspkaView() = default;

   private:
      AspkaView(const AspkaView&) = delete;
      AspkaView(AspkaView&&) = delete;
      AspkaView& operator=(const AspkaView&) = delete;
      AspkaView& operator=(AspkaView&&) = delete;
     

   };

} // namespace aspka

#endif //include guard