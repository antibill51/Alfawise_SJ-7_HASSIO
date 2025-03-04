import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

fake_fan_output_ns = cg.esphome_ns.namespace("fake_fan_output")
FakeFanOutput = fake_fan_output_ns.class_(
    "FakeFanOutput", output.FloatOutput, cg.Component
)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(FakeFanOutput),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_component(var, config)
