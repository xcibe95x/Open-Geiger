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

#define REDBUTTON_X 70
#define REDBUTTON_Y 100
#define REDBUTTON_W 100
#define REDBUTTON_H 50

#define MINPRESSURE 100
#define MAXPRESSURE 1000

XPT2046_Touchscreen ts(CS_PIN);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

boolean RecordOn = false;

void drawButton(int x, int y, int w, int h, uint16_t color, const char *label) {
  tft.fillRect(x, y, w, h, color);
  tft.drawRect(x, y, w, h, ILI9341_BLACK);

  int16_t x1, y1; // Upper-left corner of the text's bounding box
  uint16_t textWidth, textHeight; // Text's width and height

  tft.getTextBounds(label, x, y, &x1, &y1, &textWidth, &textHeight);

  // Center the text within the button
  int textX = x + (w - textWidth) / 2;
  int textY = y + (h - textHeight) / 2 + textHeight;

  tft.setCursor(textX, textY);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print(label);
}

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!");

  ts.begin();
  ts.setRotation(2);

  tft.begin();

  if (!ts.begin()) {
    Serial.println("Unable to start touchscreen.");
  } else {
    Serial.println("Touchscreen started.");
  }

  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x");
  Serial.println(x, HEX);

  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
  testText();

}

void loop() {
  // Check if the screen is touched
  TS_Point p = ts.getPoint();

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    int16_t touchX = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    int16_t touchY = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);

    if (touchX >= REDBUTTON_X && touchX <= REDBUTTON_X + REDBUTTON_W &&
        touchY >= REDBUTTON_Y && touchY <= REDBUTTON_Y + REDBUTTON_H) {
      // Button is pressed
      Serial.println("Red btn hit");
      testFillScreen();
      delay(500); // Add a delay to prevent multiple presses
    }
  }
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
  testText();
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(30, 50);
  tft.setTextColor(ILI9341_ORANGE);
  tft.setTextSize(2);
  tft.println("Youtube/xcibe95x");
    // Draw the red button
  drawButton(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED, "CLICK ME");
  return micros() - start;
}