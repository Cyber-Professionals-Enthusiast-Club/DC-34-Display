#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Pin definitions (match wiring)
const uint16_t TFT_SCLK = 36;
const uint16_t TFT_MISO = 37;
const uint16_t TFT_MOSI = 35;
const uint8_t TFT_DC   = 26; // WRB
const uint8_t TFT_CS   = 38;
const uint8_t TFT_RST  = 21;

const uint16_t LED_TORSO_YELLOW     = 3;
const uint16_t LED_TORSO_RED        = 6;
const uint16_t LED_ARM_LEFT_RED     = 12;
const uint16_t LED_ARM_LEFT_YELLOW  = 13;
const uint16_t LED_HEAD_YELLOW      = 15;
const uint16_t LED_HEAD_RED         = 16;
const uint16_t LED_LEG_RIGHT_YELLOW = 39;
const uint16_t LED_LEG_RIGHT_RED    = 40;
const uint16_t LED_LEG_LEFT_RED     = 41;
const uint16_t LED_LEG_LEFT_YELLOW  = 42;
const uint16_t LED_ARM_RIGHT_RED    = 45;
const uint16_t LED_ARM_RIGHT_YELLOW = 46;

const uint8_t PWM_BACKLIGHT = 47;
int BACKLIGHT_DUTY = 128;

const float p = 3.1415926;

////////////////////////////////////////////////////////////////////////////////
// Key addition here:
////////////////////////////////////////////////////////////////////////////////
// Configure the ESP32 to use the SPI 1 bus, which is typically used internally
// for PSRAM but the ESP32 S3 Mini 1 does not have PSRAM, so we are good to
// do this. Doing this means that Hardware SPI can be utilized instead of  
// software SPI, which is faster, and will mean a faster screen update rate. 
// Pass the SPI bus class directly to the display class in its constructor. 
// Doing this means that we are forcing it to use the hardware SPI.
////////////////////////////////////////////////////////////////////////////////
SPIClass displaySpi(FSPI);
Adafruit_ST7789 tft = Adafruit_ST7789(&displaySpi, TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////////////////////////////////////////////

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));

  const uint32_t PWM_FREQ_BACKLIGHT = 20000; // 20 kHz 
  const uint8_t  PWM_RESOLUTION = 8; 
  const uint32_t SPI_FREQUENCY = 16000000L;

  pinMode(LED_TORSO_YELLOW, OUTPUT);
  pinMode(LED_TORSO_RED, OUTPUT);
  pinMode(LED_ARM_LEFT_RED, OUTPUT);
  pinMode(LED_ARM_LEFT_YELLOW, OUTPUT);
  pinMode(LED_HEAD_YELLOW, OUTPUT);
  pinMode(LED_HEAD_RED, OUTPUT);
  pinMode(LED_LEG_RIGHT_YELLOW, OUTPUT);
  pinMode(LED_LEG_RIGHT_RED, OUTPUT);
  pinMode(LED_LEG_LEFT_RED, OUTPUT);
  pinMode(LED_LEG_LEFT_YELLOW, OUTPUT);
  pinMode(LED_ARM_RIGHT_RED, OUTPUT);

  digitalWrite(LED_TORSO_RED, HIGH);
  
  bool pwmBackightAttachSuccess = ledcAttach(PWM_BACKLIGHT, PWM_FREQ_BACKLIGHT, PWM_RESOLUTION);
  ledcWrite(PWM_BACKLIGHT, BACKLIGHT_DUTY);

  ////////////////////////////////////////////////////////////////////////////////
  // Key addition here:
  ////////////////////////////////////////////////////////////////////////////////
  // Set SPI speed after the tft display has been initialized because the tft 
  // init call will set SPI to a default frequency. 
  ////////////////////////////////////////////////////////////////////////////////
  displaySpi.begin(TFT_SCLK, TFT_MISO, TFT_MOSI);
  tft.init(240, 320);
  tft.setSPISpeed(SPI_FREQUENCY);
  ////////////////////////////////////////////////////////////////////////////////
  
  tft.setRotation(1); 
  
  Serial.println(F("Initialized"));

  Serial.print("SPI_HAS_TRANSACTION: ");
  Serial.println(SPI_HAS_TRANSACTION);

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);
  
  Serial.println("done");
  delay(1000);
}

void loop() {
  digitalWrite(LED_TORSO_RED, HIGH);
  tft.fillScreen(ST77XX_RED);
  delay(500);
  digitalWrite(LED_TORSO_RED, LOW);
  tft.fillScreen(ST77XX_GREEN);
  delay(500);
  digitalWrite(LED_TORSO_RED, HIGH);
  tft.fillScreen(ST77XX_MAGENTA);
  delay(500);
  digitalWrite(LED_TORSO_RED, LOW);
  tft.fillScreen(ST77XX_YELLOW);
  delay(500);
}

