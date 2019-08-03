#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <NTPClient.h>           //https://github.com/arduino-libraries/NTPClient

// Necessary libraries for WiFiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

// FastLED Variables
#define NUM_LEDS_HR      14
#define NUM_LEDS_MN      14
#define DATA_PIN_HR       5  //D1
#define DATA_PIN_MN       4  //D2
#define CLOCK_BRIGHTNESS 25

// Time Animation
#define HOUR_FORMAT      12
int grad_hr     =   0;
int grad_mn     = 120;
int grad_dir_hr =   1;
int grad_dir_mn =   1;
#define TIME_ANIMATION animation_day_gradient


// Time Keeping (NTP)
long utcOffsetInSeconds_DST  = -18000;
long utcOffsetInSeconds      = -21600;
#define NTP_UPDATE_INT        900000
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int time_hour_raw =   0;
int time_hour     =   0;
int time_minute   =   0;
int time_second   =   0;
int date_month    =   0;
int date_day      =   0;

// DST Routines
bool dst_state = 1;
  // DST START
  // DST starts on the second sunday of March
  #define DST_START_MONTH   3
  #define DST_START_DAY     0
  #define DST_START_SEQ     2
  #define DST_START_HOUR    2
  int dst_start_day_count = 0;

  // DST END
  // DST Ends the first sunday of November
  #define DST_END_MONTH    11
  #define DST_END_DAY       0
  #define DST_END_SEQ       1
  #define DST_END_HOUR      2
  int dst_end_day_count   = 0;


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "north-america.pool.ntp.org", 0, NTP_UPDATE_INT);

CRGB leds_hr[NUM_LEDS_HR];
CRGB leds_mn[NUM_LEDS_MN];

DEFINE_GRADIENT_PALETTE( MyRainbow ) { // row: palette index, R, G, B
      0, 255,   0,   0,    //    Red
     50, 255, 165,   0,    // Orange
    100, 255, 255,   0,    // Yellow
    150,   0, 255,   0,    //  Green
    200,   0,   0, 255,    //   Blue
    250, 128,   0, 128,    // Purple
    255,   0,   0,   0};   //  Black
CRGBPalette16 MyRainbow_pal = MyRainbow;

void setup() {
  Serial.begin(115200);
  
  FastLED.addLeds<WS2812B, DATA_PIN_HR, RGB>(leds_hr, NUM_LEDS_HR);
  FastLED.addLeds<WS2812B, DATA_PIN_MN, RGB>(leds_mn, NUM_LEDS_MN);
  FastLED.setBrightness(CLOCK_BRIGHTNESS);
  handle_display();
  
  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("7Seg_Clock");
  Serial.println("connected... yay!");

  timeClient.setTimeOffset(utcOffsetInSeconds_DST); // this needs adjusting for startup
  timeClient.begin();
}

void loop() {
  handle_DST();
  handle_time();
  TIME_ANIMATION();
  handle_display();
  
  delay(1000);
}

void handle_DST() {
  if (dst_state) {
    //when DST is active, check for the END criteria
    if (date_month == DST_END_MONTH) {
      if (date_day = DST_END_DAY) {
        dst_end_day_count++;
        if (dst_end_day_count == DST_END_SEQ) {
          if (time_hour == DST_END_HOUR) {
            dst_state = 0;
            dst_end_day_count = 0;
            timeClient.setTimeOffset(utcOffsetInSeconds);
          }
        }
      }
    }
  } else {
    // when DST is inactive, check for the START criteria
    if (date_month == DST_START_MONTH) {
      if (date_day = DST_START_DAY) {
        dst_start_day_count++;
        if (dst_start_day_count == DST_START_SEQ) {
          if (time_hour == DST_START_HOUR) {
            dst_state = 1;
            dst_start_day_count = 0;
            timeClient.setTimeOffset(utcOffsetInSeconds_DST);
          }
        }
      }
    }
  }
}

void handle_time(){
  timeClient.update();
  time_hour_raw   = timeClient.getHours();
  time_minute = timeClient.getMinutes();
  time_second = timeClient.getSeconds();
  date_month = timeClient.getMonth();
  date_day   = timeClient.getDay();
  Serial.print("The current time is: "); Serial.print(time_hour); Serial.print(":"); Serial.print(time_minute); Serial.print(":"); Serial.println(time_second);
  if (HOUR_FORMAT == 12 && time_hour_raw > 12){
    time_hour = time_hour_raw - 12;
  } else {
    time_hour = time_hour_raw;
  }
}

void handle_display() {
  set_hr(time_hour);
  set_mn(time_minute);
  FastLED.show();
}
