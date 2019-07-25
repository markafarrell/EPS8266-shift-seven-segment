#include <Arduino.h>
#include <ShiftRegister74HC595.h>

const uint8_t number[10] = {
  0xfc, // 0
  0x60, // 1
  0xda, // 2
  0xf2, // 3
  0x66, // 4
  0xb6, // 5
  0xbe, // 6
  0xe0, // 7
  0xfe, // 8
  0xf6  // 9
};

#define NUM_SHIFT_REGISTERS 2
#define SERIAL_DATA_PIN 16 // GPIO16
#define CLOCK_PIN 14 // GPIO14
#define LATCH_PIN 13 // GPIO13
#define OUTPUT_ENABLE_PIN 12 // GPIO12

ShiftRegister74HC595 sr (NUM_SHIFT_REGISTERS, SERIAL_DATA_PIN, CLOCK_PIN, LATCH_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPUT_ENABLE_PIN, OUTPUT);
}

void loop() {
  int i = 0;
  uint8_t pinValues [2] = {0x00, 0x00};
  uint8_t onesDigit = 0;
  uint8_t tensDigit = 0;

  digitalWrite(OUTPUT_ENABLE_PIN, 0);

  tensDigit = i / 10;
  onesDigit = i % 10;
  pinValues[1] = ~number[onesDigit]; // We need bitwise not here as we are using a common anode display
  pinValues[0] = ~number[tensDigit]; // We need bitwise not here as we are using a common anode display
  sr.setAll(pinValues);

  while(1)
  {
    for(i=0; i<100; i++)
    {
      tensDigit = i / 10;
      onesDigit = i % 10;
      pinValues[1] = ~number[onesDigit]; // We need bitwise not here as we are using a common anode display
      pinValues[0] = ~number[tensDigit]; // We need bitwise not here as we are using a common anode display

      sr.setAll(pinValues);

      digitalWrite(OUTPUT_ENABLE_PIN, 1);
      delay(750);

      digitalWrite(OUTPUT_ENABLE_PIN, 0);
      delay(250);
    }
  }
}