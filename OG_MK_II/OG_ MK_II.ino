/***************************************************
  This is an example to run when installing your LCD
  to make sure it works as intended before installing
  anything else to your NodeMCU board.
  NOTE: NodeMCU does not require leveling resistors 
        unlike Arduino Nano, so you can directly
        solder the connections in place.
 ****************************************************/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"

#define CS_PIN D2

#define TS_MINX 250
#define TS_MINY 200 // calibration points for touchscreen
#define TS_MAXX 3800
#define TS_MAXY 3750

#define TFT_DC D4
#define TFT_CS D8


XPT2046_Touchscreen ts(CS_PIN);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  
  Serial.begin(38400);
  ts.begin();
  ts.setRotation(2);

  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
  testText();
  delay(2000);

}


void loop() {
     testFillScreen();
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_YELLOW);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_ORANGE);
  yield();
  tft.fillScreen(ILI9341_CYAN);
  yield();
  tft.fillScreen(ILI9341_MAGENTA);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(2, 50);
  tft.setTextColor(ILI9341_ORANGE);
  tft.setTextSize(2);
  tft.println("Youtube/xcibe95x");
  return micros() - start;
}
