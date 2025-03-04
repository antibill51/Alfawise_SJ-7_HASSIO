#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"

#include "esphome/core/log.h"
#include "esphome/core/application.h"
      

namespace esphome {
namespace uart_readline_custom {
  class UartReadLineSensor : public text_sensor::TextSensor, 
                              public uart::UARTDevice, 
                              public Component {
   public:
      explicit UartReadLineSensor(uart::UARTComponent *parent);

      void setup() override;
      void loop() override;

      static int pos;
      static char buffer[];
      static constexpr int max_line_length = 80;

 private:
  char outputBuffer[3];
  int j = 0;
  int startMarker = 0x55;
  int secondMarker = 0xAA;
  int timeOut = 50;
  bool receiveUntilTimeout;
  bool valuesending = false;
  int timeReceived;

  void byte2HexStr(byte val, char* outputBuffer);
  int sendvalue(char* buffer, bool valuesending);
  int storevalue(char* buffer, int readch, bool UntilTimeout, bool valuesending);
};

}  // namespace uart_readline_custom
}  // namespace esphome
