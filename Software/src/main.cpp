#include <Arduino.h>

// Library Dependencies
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// FastLED Setup
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

// NTPClient Setup
#include <NTP.h>

// WifiManager Setup
#include <WiFiManager.h>

#include "Common.h"
#include "Segments_Hour.h"
#include "Segments_Minute.h"
#include "Animations.h"

// FastLED Variables
#define NUM_LEDS_HR                14
#define NUM_LEDS_MN                14
#define DATA_PIN_HR                 5  //D1
#define DATA_PIN_MN                 4  //D2

// Brightness Variables
#define BRIGHTNESS_START            5
#define BRIGHTNESS_MAX            100
#define BRIGHTNESS_MIN              3
#define BRIGHTNESS_READ_MIN       100
#define BRIGHTNESS_READ_MAX       850
#define BRIGHTNESS_ERR_THRESH       5
#define BRIGHTNESS_CH_RATE_FAST     5
#define BRIGHTNESS_CH_RATE_SLOW     1
#define BRIGHTNESS_RATE_THRESH     10
int brightness_set;
int brightness_err      =           0;

// Time Animation
#define HOUR_FORMAT                12
int grad_hr             =           0;                // default values, used in starting animation
int grad_mn             =         120;                // default values, used in starting animation
int grad_dir_hr         =           1;
int grad_dir_mn         =           1;
#define TIME_ANIMATION              5
  // TIME_ANIMATION available options:
  //    1 - animation_cycle
  //    2 - animation_day_gradient
  //    3 - animation_hour_gradient
  //    4 - animation_min_gradient
  //    5 - animation_const (need to set grad_const to int 0-255)
  #ifdef TIME_ANIMATION == 3
    int grad_const = 200;
  #endif

// Time Keeping (NTP)
long utcOffsetInSeconds_DST  = -18000;
long utcOffsetInSeconds      = -21600;
#define NTP_UPDATE_INT         900000
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int time_hour_raw      =            0;
int time_hour          =            0;
int time_minute        =            0;
int time_second        =            0;
//int date_month         =            0;
//int date_day           =            0;


// DST Routines
bool DST_flag          =            0;
bool dst_state         =            1;               // default DST state
  // DST START
  // DST starts on the second sunday of March
  #define DST_START_MONTH           3
  #define DST_START_DAY             0
  #define DST_START_SEQ             2
  #define DST_START_HOUR            2

  // DST END
  // DST Ends the first sunday of November
  #define DST_END_MONTH            11
  #define DST_END_DAY               0
  #define DST_END_SEQ               1
  #define DST_END_HOUR              2

WiFiUDP ntpUDP;
NTP ntp(ntpUDP);

CRGB leds_hr[NUM_LEDS_HR];
CRGB leds_mn[NUM_LEDS_MN];

DEFINE_GRADIENT_PALETTE( MyRainbow ) { // row: palette index, R, G, B
      0, 255,   0,   0,    //    Red
     40, 255, 165,   0,    // Orange
     80, 255, 255,   0,    // Yellow
    120,   0, 255,   0,    //  Green
    160,   0,   0, 255,    //   Blue
    200, 128,   0, 128,    // Purple
    240, 255,   0,   0,    //    Red
    255,   0,   0,   0};   //  Black
CRGBPalette16 MyRainbow_pal = MyRainbow;

// #include <loop_handles.cpp>
void handle_time();
void handle_display();
void handle_brightness();



void setup() {
  Serial.begin(115200);
  
  // Fastled
  FastLED.addLeds<WS2812B, DATA_PIN_HR, GRB>(leds_hr, NUM_LEDS_HR);
  FastLED.addLeds<WS2812B, DATA_PIN_MN, GRB>(leds_mn, NUM_LEDS_MN);
  FastLED.setBrightness(BRIGHTNESS_START);
  handle_display();
  
  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("7Seg_Clock");
  Serial.println("connected... yay!");

  // NTP Handling
  ntp.updateInterval(900000);
  ntp.ntpServer("north-america.pool.ntp.org");
  ntp.ruleDST("CDT", Second, Sun, Mar, 2, -300);
  ntp.ruleSTD("CST",  First, Sun, Nov, 3, -360);
  ntp.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  handle_time();
  handle_animation(TIME_ANIMATION);
  handle_display();

  Serial.println();

  delay(1000);
}

void handle_time(){
  ntp.update();
  time_hour_raw = ntp.hours();
  time_minute   = ntp.minutes();
  time_second   = ntp.seconds();
  //date_month = timeClient.getMonth();
  //date_day   = timeClient.getDay();
  Serial.print("The current time is: "); Serial.print(time_hour); Serial.print(":"); Serial.print(time_minute); Serial.print(":"); Serial.println(time_second);
  if (HOUR_FORMAT == 12 ) {
    // Format the time for 12 hour readibility
    if ( time_hour_raw > 12) {
      // hours 13-23
      time_hour = time_hour_raw - 12;
    } else if (time_hour_raw == 0) {
      // convert hour 0 to 12
      time_hour = 12;
    } else {
      // set the remaining hours
      time_hour = time_hour_raw;
    }
  }
}

void handle_display() {
  handle_brightness();
  
  set_hr(time_hour);
  set_mn(time_minute);
  FastLED.show();
}

void handle_brightness() {
  int a_read = analogRead(A0);
  int brightness_new = map(a_read,BRIGHTNESS_READ_MIN,BRIGHTNESS_READ_MAX,BRIGHTNESS_MIN,BRIGHTNESS_MAX);
  Serial.print("Analog read, brightness_set, brightness_new "); Serial.print(a_read); Serial.print(", "); Serial.print(brightness_set); Serial.print(", "); Serial.println(brightness_new);
  brightness_err = brightness_err + (brightness_new-brightness_set);
  //Serial.print("brightness_err: "); Serial.println(brightness_err);
  
  if (abs(brightness_err) >= BRIGHTNESS_ERR_THRESH) {
    int brightness_change;
    if (abs(brightness_err) > BRIGHTNESS_RATE_THRESH ) {
      brightness_change = (abs(brightness_err)/brightness_err) * BRIGHTNESS_CH_RATE_FAST;
    } else {
      brightness_change = (abs(brightness_err)/brightness_err) * BRIGHTNESS_CH_RATE_SLOW;
    }
    brightness_set = brightness_set + brightness_change;
    brightness_err = 0;
    if (brightness_set > BRIGHTNESS_MAX) {
      brightness_set = BRIGHTNESS_MAX;
    } else if (brightness_set < BRIGHTNESS_MIN ) {
      brightness_set = BRIGHTNESS_MIN;
    }
    //Serial.print("Analog read, led_brightness "); Serial.print(a_read); Serial.print(", "); Serial.println(brightness_set);
    Serial.print("Setting new brightness: "); Serial.println(brightness_set);
    FastLED.setBrightness(brightness_set);
  }
}
