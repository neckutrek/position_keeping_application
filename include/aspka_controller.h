#ifndef ASPKA_CONTROLLER_H
#define ASPKA_CONTROLLER_H

namespace aspka {
   
   /** @brief 
    */
   class AspkaController {
   public:
      AspkaController() = default;
      ~AspkaController() = default;

   private:
      AspkaController(const AspkaController&) = delete;
      AspkaController(AspkaController&&) = delete;
      AspkaController& operator=(const AspkaController&) = delete;
      AspkaController& operator=(AspkaController&&) = delete;
     

   };

} // namespace aspka

#endif //include guard