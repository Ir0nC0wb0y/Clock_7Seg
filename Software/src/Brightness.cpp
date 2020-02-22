#include "Common.h"

// Common Brightness variables
#define BRIGHTNESS_MAX            100
#define BRIGHTNESS_MIN              1

// Log Scale Brightness
  // logarithmic regression analysis taken from https://keisan.casio.com/exec/system/14059930226691
  // Values:
  //   X   |  Y  
  // ------|------
  //    5  |   1
  //   25  |  50
  //   75  |  90
  //   90  | 100
#define LOG_SCALE_A          -133.603
#define LOG_SCALE_B            33.802

// Exponential Brightness
  //                      1001
  // brightness = --------------------
  //               ( 1 - e^-(x/A - B))
  #define EXP_SCALE_A             10
  #define EXP_SCALE_B             12

// Old Style Brightness
//#define BRIGHTNESS_START            5
#define BRIGHTNESS_READ_MIN       100
#define BRIGHTNESS_READ_MAX       850
#define BRIGHTNESS_ERR_THRESH       5
#define BRIGHTNESS_CH_RATE_FAST     5
#define BRIGHTNESS_CH_RATE_SLOW     1
#define BRIGHTNESS_RATE_THRESH     10

void brightness_logic(int analog_read, int brightness_new) {
  if (brightness_new < brightness_set) {
    brightness_set--;
  } else if ( brightness_new > brightness_set) {
    brightness_set++;
  }

  if (brightness_set > BRIGHTNESS_MAX){
    brightness_set = BRIGHTNESS_MAX;
  } else if ( brightness_set < BRIGHTNESS_MIN ) {
    brightness_set = BRIGHTNESS_MIN;
  }

  FastLED.setBrightness(brightness_set);

  Serial.print("Analog: "); Serial.print(analog_read); Serial.print(" brightness_new: "); Serial.print(brightness_new); Serial.print(", brightness_set: "); Serial.print(brightness_set);
}

void handle_brightness_old() {
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

void handle_brightness_log() {
  int analog_read = analogRead(A0);
  int brightness_new = LOG_SCALE_A + LOG_SCALE_B * log(analog_read);

  brightness_logic(analog_read, brightness_new);
}

void handle_brightness_exp() {
  int analog_read = analogRead(A0);
  int brightness_new = 101 / ( 1 + exp( -1 * (analog_read/EXP_SCALE_A - EXP_SCALE_B)));

  brightness_logic(analog_read, brightness_new);
}