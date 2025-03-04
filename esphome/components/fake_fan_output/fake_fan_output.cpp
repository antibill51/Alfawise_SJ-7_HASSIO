#include "fake_fan_output.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace fake_fan_output {

static const char *TAG = "fake_fan_output";

void FakeFanOutput::write_state(float state) {
    static uint32_t last_change = 0;
    uint32_t now = millis();

    if (now - last_change < 500) {  
        ESP_LOGD("fake_fan_output", "Change ignored");
        return;
    }
    
    last_change = now;

    if (state < 0.1) {
        ESP_LOGD("fake_fan_output", "Fan OFF");
    } else if (state < 0.5) {
        ESP_LOGD("fake_fan_output", "Fan LOW speed");
    } else {
        ESP_LOGD("fake_fan_output", "Fan HIGH speed");
    }
}

}  // namespace fake_fan_output
}  // namespace esphome
