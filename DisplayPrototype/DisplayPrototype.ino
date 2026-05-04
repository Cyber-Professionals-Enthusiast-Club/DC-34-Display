#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Pin definitions (match wiring)
#define TFT_SCLK 36
#define TFT_MISO 37
#define TFT_MOSI 35
#define TFT_DC   26 // WRB
#define TFT_CS   38
#define TFT_RST  21

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC,
      TFT_MOSI, TFT_SCLK, TFT_RST, -1);

void setup() {
  Serial.begin(115200);

  tft.begin();

  tft.setRotation(1); // Landscape
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.setCursor(40, 120);

  tft.println("Hello World!");
}

void loop() {
  // nothing needed
}
