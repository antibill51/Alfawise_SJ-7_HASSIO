#pragma once
#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace fake_fan_output {

class FakeFanOutput : public output::FloatOutput, public Component {
 public:
    void write_state(float state) override;
};

}  // namespace fake_fan_output
}  // namespace esphome
