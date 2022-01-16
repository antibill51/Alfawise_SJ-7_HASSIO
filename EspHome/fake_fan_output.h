#include "esphome.h"
using namespace esphome;

class FakeFanOutput : public Component, public FloatOutput {
  public:
    void write_state(float state) override {
      if (state < 0.1) {
        // OFF
        
      } else if (state < 0.5) {
        // low speed
         
      } else {
        // high speed
         
      }
    }
};