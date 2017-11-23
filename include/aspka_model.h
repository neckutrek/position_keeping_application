#ifndef ASPKA_MODEL_H
#define ASPKA_MODEL_H

namespace aspka {
   
   /** @brief 
    */
   class AspkaModel {
   public:
      AspkaModel() = default;
      ~AspkaModel() = default;

   private:
      AspkaModel(const AspkaModel&) = delete;
      AspkaModel(AspkaModel&&) = delete;
      AspkaModel& operator=(const AspkaModel&) = delete;
      AspkaModel& operator=(AspkaModel&&) = delete;
     

   };

} // namespace aspka

#endif //include guard