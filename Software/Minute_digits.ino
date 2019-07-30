void set_mn(int min_number) {
  int min_digit[2];
  min_digit[1] = min_number % 10;
  min_digit[0] = ( min_number - min_digit[1] ) / 10;
  //Serial.print("Time: "); Serial.print(min_number); Serial.print(" , digits (1,2): ("); Serial.print(min_digit[0]); Serial.print(","); Serial.print(min_digit[1]); Serial.println(")");

  for (int i=0; i < 2; i++) {
    switch (min_digit[i]) {
      case 0:
        set_mn_0(i*7);
        break;
      case 1:
        set_mn_1(i*7);
        break;
      case 2:
        set_mn_2(i*7);
        break;
      case 3:
        set_mn_3(i*7);
        break;
      case 4:
        set_mn_4(i*7);
        break;
      case 5:
        set_mn_5(i*7);
        break;
      case 6:
        set_mn_6(i*7);
        break;
      case 7:
        set_mn_7(i*7);
        break;
      case 8:
        set_mn_8(i*7);
        break;
      case 9:
        set_mn_9(i*7);
        break;
    }
  }
}

void set_mn_0(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 3
  leds_mn[array_start+3] = CRGB::Black;                              // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 7
}

void set_mn_1(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = CRGB::Black;                              // LED 2
  leds_mn[array_start+2] = CRGB::Black;                              // LED 3
  leds_mn[array_start+3] = CRGB::Black;                              // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = CRGB::Black;                              // LED 6
  leds_mn[array_start+6] = CRGB::Black;                              // LED 7
}

void set_mn_2(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = CRGB::Black;                              // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = CRGB::Black;                              // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 7
}

void set_mn_3(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = CRGB::Black;                              // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = CRGB::Black;                              // LED 7
}

void set_mn_4(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = CRGB::Black;                              // LED 2
  leds_mn[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = CRGB::Black;                              // LED 6
  leds_mn[array_start+6] = CRGB::Black;                              // LED 7
}

void set_mn_5(int array_start) {
  leds_mn[array_start]   = CRGB::Black;                              // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = CRGB::Black;                              // LED 7
}

void set_mn_6(int array_start) {
  leds_mn[array_start]   = CRGB::Black;                              // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 7
}

void set_mn_7(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = CRGB::Black;                              // LED 3
  leds_mn[array_start+3] = CRGB::Black;                              // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = CRGB::Black;                              // LED 6
  leds_mn[array_start+6] = CRGB::Black;                              // LED 7
}

void set_mn_8(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 7
}

void set_mn_9(int array_start) {
  leds_mn[array_start]   = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 1
  leds_mn[array_start+1] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 2
  leds_mn[array_start+2] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 3
  leds_mn[array_start+3] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 4
  leds_mn[array_start+4] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 5
  leds_mn[array_start+5] = ColorFromPalette(MyRainbow_pal, grad_mn); // LED 6
  leds_mn[array_start+6] = CRGB::Black;                              // LED 7
}
