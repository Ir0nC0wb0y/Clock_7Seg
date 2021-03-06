void set_hr(int hour_number) {
  int hour_digit[2];
  hour_digit[0] = hour_number % 10;
  hour_digit[1] = ( hour_number - hour_digit[0] ) / 10;
  //Serial.print("Time: "); Serial.print(hour_number); Serial.print(" , digits (1,2): ("); Serial.print(hour_digit[0]); Serial.print(","); Serial.print(hour_digit[1]); Serial.println(")");

  for (int i=0; i < 2; i++) {
    switch (hour_digit[i]) {
      case 0:
        if (i == 0) {
          set_hr_0(i*7);
        } else if (i == 1) {
          if (hour_digit[0] == 0) {
            set_hr_0(i*7);
          } else {
            set_hr_off(i*7);
          }
        }
        break;
      case 1:
        set_hr_1(i*7);
        break;
      case 2:
        set_hr_2(i*7);
        break;
      case 3:
        set_hr_3(i*7);
        break;
      case 4:
        set_hr_4(i*7);
        break;
      case 5:
        set_hr_5(i*7);
        break;
      case 6:
        set_hr_6(i*7);
        break;
      case 7:
        set_hr_7(i*7);
        break;
      case 8:
        set_hr_8(i*7);
        break;
      case 9:
        set_hr_9(i*7);
        break;
    }
  }
}

void set_hr_off(int array_start) {
  leds_hr[array_start]   = CRGB::Black;                              // LED 1
  leds_hr[array_start+1] = CRGB::Black;                              // LED 2
  leds_hr[array_start+2] = CRGB::Black;                              // LED 3
  leds_hr[array_start+3] = CRGB::Black;                              // LED 4
  leds_hr[array_start+4] = CRGB::Black;                              // LED 5
  leds_hr[array_start+5] = CRGB::Black;                              // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}

void set_hr_0(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 3
  leds_hr[array_start+3] = CRGB::Black;                              // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 7
}

void set_hr_1(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = CRGB::Black;                              // LED 2
  leds_hr[array_start+2] = CRGB::Black;                              // LED 3
  leds_hr[array_start+3] = CRGB::Black;                              // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = CRGB::Black;                              // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}

void set_hr_2(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = CRGB::Black;                              // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = CRGB::Black;                              // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 7
}

void set_hr_3(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = CRGB::Black;                              // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}

void set_hr_4(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = CRGB::Black;                              // LED 2
  leds_hr[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = CRGB::Black;                              // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}

void set_hr_5(int array_start) {
  leds_hr[array_start]   = CRGB::Black;                              // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}

void set_hr_6(int array_start) {
  leds_hr[array_start]   = CRGB::Black;                              // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 7
}

void set_hr_7(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = CRGB::Black;                              // LED 3
  leds_hr[array_start+3] = CRGB::Black;                              // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = CRGB::Black;                              // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}

void set_hr_8(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 7
}

void set_hr_9(int array_start) {
  leds_hr[array_start]   = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 1
  leds_hr[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 2
  leds_hr[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 3
  leds_hr[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 4
  leds_hr[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 5
  leds_hr[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_hr); // LED 6
  leds_hr[array_start+6] = CRGB::Black;                              // LED 7
}
