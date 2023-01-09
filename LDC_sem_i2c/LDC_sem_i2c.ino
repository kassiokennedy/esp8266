//https://diyi0t.com/lcd-display-tutorial-for-arduino-and-esp8266/
// https://dvtecnologia.com.br/imagens/HC1627-SYH-I2C-30_Eng%2CA.pdf - datasheet do display 
/*
#include <LiquidCrystal.h>

#define PIN_WIRE_SDA (4)
#define PIN_WIRE_SCL (5)

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;

int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
                         // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
                      // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

/*
*/
// https://diyi0t.com/lcd-display-tutorial-for-arduino-and-esp8266/
// include the library code:
// #include "LiquidCrystal_I2C.h"
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
const int RS = 4, EN = 0, d4 = 12 , d5 = 13, d6 = 15, d7 = 3;

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
// Print a message to the LCD.
lcd.print("hello, world!");
}

void loop() {
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 1);
// print the number of seconds since reset:
lcd.print(millis() / 1000);
}
