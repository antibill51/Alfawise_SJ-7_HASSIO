import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, uart
from esphome.const import CONF_ID

uart_readline_custom_ns = cg.esphome_ns.namespace("uart_readline_custom")
UartReadLineSensor = uart_readline_custom_ns.class_("UartReadLineSensor", text_sensor.TextSensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(UartReadLineSensor)
    .extend(
        {
            cv.GenerateID(): cv.declare_id(UartReadLineSensor),
            cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], await cg.get_variable(config["uart_id"]))
    await text_sensor.register_text_sensor(var, config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
