#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <NTPClient.h>

// Necessary libraries for WiFiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

// FastLED Variables
#define NUM_LEDS_HR      14
#define NUM_LEDS_MN      14
#define DATA_PIN_HR       5  //D1
#define DATA_PIN_MN       4  //D2
#define CLOCK_BRIGHTNESS  5

// Time Animation
#define HOUR_FORMAT      12
int grad_hr     =   0;
int grad_mn     = 120;
int grad_dir_hr =   1;
int grad_dir_mn =   1;
int time_hour   =   0;
int time_minute =   0;
int time_second =   0;

// Time Keeping (NTP)
const long utcOffsetInSeconds = -18000;
char dasOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "north-america.pool.ntp.org", utcOffsetInSeconds);

CRGB leds_hr[NUM_LEDS_HR];
CRGB leds_mn[NUM_LEDS_MN];

DEFINE_GRADIENT_PALETTE( MyRainbow ) { // row: palette index, R, G, B
      0, 255,   0,   0,    //    Red
     50, 255, 255,   0,    // Yellow
    100,   0, 255,   0,    //  Green
    150,   0, 255, 255,    //   Cyan
    200,   0,   0, 255,    //   Blue
    250, 255,   0, 255,    // Purple
    255,   0,   0,   0};   //  Black
CRGBPalette16 MyRainbow_pal = MyRainbow;

void setup() {
  Serial.begin(115200);

  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("7Seg_Clock");
  Serial.println("connected... yay!");

  timeClient.begin();
  
  Serial.println("Starting Animation");
  FastLED.addLeds<WS2812B, DATA_PIN_HR, RGB>(leds_hr, NUM_LEDS_HR);
  FastLED.addLeds<WS2812B, DATA_PIN_MN, RGB>(leds_mn, NUM_LEDS_MN);
  FastLED.setBrightness(CLOCK_BRIGHTNESS);
}

void loop() {
  if (grad_hr == 0) {
    grad_dir_hr = 1;
  } else if (grad_hr == 250) {
    grad_dir_hr = -1;
  }
  grad_hr = grad_hr + grad_dir_hr;

  if (grad_mn == 0) {
    grad_dir_mn = 1;
  } else if (grad_mn == 250) {
    grad_dir_mn = -1;
  }
  grad_mn = grad_mn + grad_dir_mn;

  timeClient.update();
  time_hour   = timeClient.getHours();
  time_minute = timeClient.getMinutes();
  time_second = timeClient.getSeconds();
  Serial.print("The current time is: "); Serial.print(time_hour); Serial.print(":"); Serial.print(time_minute); Serial.print(":"); Serial.println(time_second);
  if (HOUR_FORMAT == 12 && time_hour > 12){
    time_hour = time_hour - 12;
  }
  
  //Serial.print("setting new color (grad_hr, grad_mn): ("); Serial.print(grad_hr); Serial.print(","); Serial.print(grad_mn); Serial.println(")");
  // set LEDS in the set to the new color
  set_hr(time_hour);
  set_mn(time_minute);
  FastLED.show();

  delay(1000);
}
