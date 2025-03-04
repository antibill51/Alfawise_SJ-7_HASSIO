#include "uart_readline_custom.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uart_readline_custom {

int UartReadLineSensor::pos = 0;
char UartReadLineSensor::buffer[UartReadLineSensor::max_line_length] = {0};

static const char *TAG = "uart_readline_custom";  

UartReadLineSensor::UartReadLineSensor(uart::UARTComponent *parent) : 
    uart::UARTDevice(parent) {}

void UartReadLineSensor::byte2HexStr(byte val, char* outputBuffer) {
    const char HEX_DIGITS[17] = "0123456789ABCDEF";
    outputBuffer[0] = HEX_DIGITS[(val & 0xf0) >> 4];
    outputBuffer[1] = HEX_DIGITS[val & 0xf];
    outputBuffer[2] = '\0';
}

void UartReadLineSensor::setup() {
    ESP_LOGD(TAG, "UART ReadLine Sensor initialized");
}

int UartReadLineSensor::sendvalue(char* buffer, bool valuesending) {  
	valuesending = true;

    std::string myStrObject;
    myStrObject.reserve(40);
	myStrObject = "";
    for(int i = max_line_length; i > 0; i--) {
      if (j == 0) {				
        if (buffer[i] > 0 ) {
          j = i + 1;
          break;
        }
      }
    }
    // convert to hex
    for(int i = 0; i < j; i++) {
      byte2HexStr(buffer[i], outputBuffer);
      myStrObject += outputBuffer;
      // add separator except for the last element
      if(i < j - 1) {
        myStrObject += ":";
      }
    }
    // publish result
    publish_state(myStrObject.c_str());
    ESP_LOGD(TAG, "Sending complete message: %s", myStrObject.c_str());
    publish_state(myStrObject);
    // reset var
    j = 0;
    pos = 0;
    for( int i = 0; i < max_line_length + 1;  ++i )
    buffer[i] = (char)0;
    valuesending = false;
    return 1;
}

int UartReadLineSensor::storevalue(char* buffer, int readch, bool UntilTimeout, bool valuesending) {
    while (valuesending) {
        delay(200);
    }
    buffer[pos++] = readch;
    buffer[pos] = 0;
    if (UntilTimeout) {
        receiveUntilTimeout = true;
    }
    timeReceived = millis();
    return 1;
}

void UartReadLineSensor::loop() {
    int readch;
    if (available() >= 1 && !receiveUntilTimeout) {
        readch = read();
        if (readch == startMarker) {
            storevalue(buffer, readch, true, valuesending);
        }
    }

    if (receiveUntilTimeout) {
        if (available() > 0) {
            readch = read();
            if (readch == startMarker) {
                sendvalue(buffer,valuesending);
            }
            if (readch == secondMarker) {
                if (pos > 1 ) {
                    sendvalue(buffer, valuesending);
                    storevalue(buffer, startMarker, false, valuesending);
                }
            }
            storevalue(buffer, readch, false, valuesending);
        } else {
            if (millis() - timeReceived >= timeOut) {
                receiveUntilTimeout = false;
                sendvalue(buffer,valuesending);
            }
        }
    }
}

}  // namespace uart_readline_custom
}  // namespace esphome
