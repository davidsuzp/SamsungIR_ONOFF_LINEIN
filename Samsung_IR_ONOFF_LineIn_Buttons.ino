/*
 * Based on SimpleSender and receiver from https://github.com/Arduino-IRremote/Arduino-IRremote.
 * and adding the pattern from Button sample.
 * the program, actuate sending IRsignals for Power ON/OFF and LineIn function on the TV
 * for the SAMSUNG TV model TX-20C5DF, TX20C5DF3x/XEC  
 *  Copyright (C) 2023  David Suz
 *  davidsuzp@hotmail.com
 *
 *  MIT License
 */
#include <Arduino.h>

#define DISABLE_CODE_FOR_RECEIVER // Disables restarting receiver after each send. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not used.

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

const int btPinPower = 4;  // the number of the pushbutton pin for Power ON/OFF
const int btPinLineIn = 5; // the number of the pushbutton pin for Line/In

int btStatePower = 0; // variable for reading the pushbutton Power ON/Off status
int btStateLineIn = 0; // variable for reading the pushbutton Line In status

void setup() {
    // initialize the LED pin as an output
    pinMode(LED_BUILTIN, OUTPUT);

    // initialize the Power and LedIn button pin as an input
    pinMode(btPinPower, INPUT);
    pinMode(btPinLineIn, INPUT);

    Serial.begin(115200);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

    /*
     * The IR library setup. That's all!
     */
    IrSender.begin(DISABLE_LED_FEEDBACK); // Start with IR_SEND_PIN as send pin and disable feedback LED at default feedback LED pin
}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */
uint8_t sCommand_OnOff = 0x2; // Specific command Power On/Off for Samsung TX-20C5DF // TX-20C5DF3X/XEC
uint8_t sCommand_LineIn = 0x24; // Specific command Power On/Off for Samsung TX-20C5DF // TX-20C5DF3X/XEC
uint8_t sRepeats = 0; // No repeats only one shot

void loop() {

    btStatePower = digitalRead(btPinPower);
    btStateLineIn = digitalRead(btPinLineIn);
    if (btStatePower == HIGH) // Button Power ON/OFF was pressed
    {
    /*
     * Print current send values
     */
    Serial.println();
    Serial.print(F("Send now: address=0x505, command=0x2, --POWER--"));
    Serial.print(sCommand_OnOff, HEX);
    Serial.print(F(", repeats="));
    Serial.print(sRepeats);
    Serial.println();

    Serial.println(F("Send standard SAMSUNG with command 2 Power"));
    Serial.flush();

    IrSender.sendSamsung(0x505, sCommand_OnOff, sRepeats);
    }
    if (btStateLineIn == HIGH) // Button Line In was pressed
    {
      Serial.println();
      Serial.print(F("Send now: address=0x505, command=0x24, --POWER--"));
      Serial.print(sCommand_LineIn, HEX);
      Serial.print(F(", repeats="));
      Serial.print(sRepeats);
      Serial.println();

      Serial.println(F("Send standard SAMSUNG with command 24 LineIn"));
      Serial.flush();

      IrSender.sendSamsung(0x505, sCommand_LineIn, sRepeats);
    }
    
}
 
