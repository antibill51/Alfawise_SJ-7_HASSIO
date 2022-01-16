#include "esphome.h"



static int pos = 0;
char outputBuffer[3];
const int max_line_length = 80;
static char buffer[max_line_length];
int j = 0;
int startMarker = 0x55;
int secondMarker = 0xAA;
int timeOut = 50;
bool receiveUntilTimeout;
bool valuesending = false;
int timeReceived;

class UartReadLineSensor : public Component, public UARTDevice, public TextSensor {
 public:
  UartReadLineSensor(UARTComponent *parent) : UARTDevice(parent) {}


// Helper function for converting byte value to 2-digit hex string
  void byte2HexStr(byte val, char* outputBuffer){

    const char HEX_DIGITS[17] = "0123456789ABCDEF";

    byte upper_nibble_index = (val & 0xf0) >> 4;
    byte lower_nibble_index = val & 0xf;

    outputBuffer[0] = HEX_DIGITS[upper_nibble_index];
    outputBuffer[1] = HEX_DIGITS[lower_nibble_index];
    outputBuffer[2] = '\0';
  }


  void setup() override {
    // nothing to do here
  }

  int sendvalue(char* buffer, bool valuesending)
  {
    valuesending = true;
    std::string myStrObject;
    myStrObject = "";
    // buffer size
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
    // reset var
    j = 0;
    pos = 0;
    for( int i = 0; i < max_line_length + 1;  ++i )
    buffer[i] = (char)0;
    valuesending = false;
    return 1;
  }

  // Store values
  int storevalue(char* buffer, int readch, bool UntilTimeout, bool valuesending)
  {
    while (valuesending == true) {
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

  void loop() override {
    int readch;
    if (available() >= 1 && !receiveUntilTimeout) {
      readch = Serial.read();
      if (readch == startMarker) {
        storevalue(buffer, readch, true, valuesending);
      }
    }
    if (receiveUntilTimeout) {
      if (Serial.available() > 0)
      {
        readch = Serial.read();
        if (readch == startMarker) {
          sendvalue(buffer,valuesending);
        }
        if (readch == secondMarker) {
          if (pos > 1 ) {
            sendvalue(buffer,valuesending);
            storevalue(buffer, 0x55, false, valuesending);
          }
        } 
        storevalue(buffer, readch, false, valuesending);
      }
      else //Serial.available == 0 and nothing to read
      {
        if (millis() - timeReceived >= timeOut)
        {
          receiveUntilTimeout = false;
          sendvalue(buffer,valuesending);
        }
      }     
    }
  }
};