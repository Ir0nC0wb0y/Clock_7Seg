#include <FastLED.h>

// FastLED Variables
#define NUM_LEDS_HR                14
#define NUM_LEDS_MN                14

// Brightness Variables
extern int brightness_set;
extern int brightness_err;
extern CRGBPalette16 MyRainbow_pal;
extern CRGB leds_hr[NUM_LEDS_HR];
extern CRGB leds_mn[NUM_LEDS_MN];

// Time Animation
extern int grad_hr;                // default values, used in starting animation
extern int grad_mn;                // default values, used in starting animation
extern int grad_dir_hr;
extern int grad_dir_mn;
extern int grad_const;

// Time Keeping (NTP)
extern long utcOffsetInSeconds_DST;
extern long utcOffsetInSeconds;
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
extern int time_hour_raw;
extern int time_hour;
extern int time_minute;
extern int time_second;
extern int date_month;
extern int date_day;