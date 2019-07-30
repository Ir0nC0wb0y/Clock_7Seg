#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

// FastLED Variables
#define NUM_LEDS_HR      14
#define NUM_LEDS_MN      14
#define DATA_PIN_HR       5  //D1
#define DATA_PIN_MN       4  //D2
#define CLOCK_BRIGHTNESS  5

// Time Animation
int grad_hr = 0;
int grad_mn = 120;
int grad_dir_hr = 1;
int grad_dir_mn = 1;
int time_hour = 0;

bool first_loop = 1;

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

  time_hour = time_hour + 1;
  if (time_hour == 100) {
    time_hour = 0;
  }
  
  Serial.print("setting new color (grad_hr, grad_mn): ("); Serial.print(grad_hr); Serial.print(","); Serial.print(grad_mn); Serial.println(")");
  // set LEDS in the set to the new color
  set_hr(time_hour);
  set_mn(time_hour);
  FastLED.show();

  delay(250);
}
