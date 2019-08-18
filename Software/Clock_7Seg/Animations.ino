void handle_animation(int animation_func) {
  //Serial.print("animation_func: "); Serial.print(animation_func);
  switch (animation_func) {
    case 1:
      //Serial.println(" running animation_cycle");
      animation_cycle();
      break;
    case 2:
      //Serial.println(" running animation_day_gradient");
      animation_day_gradient();
      break;
    case 3:
      //Serial.println(" running animation_hour_gradient");
      animation_hour_gradient();
      break;
    case 4:
      //Serial.println(" running animation_min_gradient");
      animation_min_gradient();
      break;
    case 5:
      //Serial.println(" running animation_const");
      animation_const();
      break;
  }
}

void animation_cycle() {
  // handle animation(1)
  if (grad_hr == 0) {
    grad_dir_hr = 1;
  } else if (grad_hr == 240) {
    grad_dir_hr = -1;
  }
  grad_hr = grad_hr + grad_dir_hr;

  if (grad_mn == 0) {
    grad_dir_mn = 1;
  } else if (grad_mn == 240) {
    grad_dir_mn = -1;
  }
  grad_mn = grad_mn + grad_dir_mn;
}

void animation_day_gradient() {
  // handle_animation(2)
  double day_percent;
  int day_gradient;
  day_percent = (time_hour_raw/24.0 + time_minute/1440.0 + time_second/86400.0)*100;
  day_gradient = map_double(day_percent, 0, 100, 0, 240);
  //Serial.print("(day_percent, day_gradient): ("); Serial.print(day_percent); Serial.print(", "); Serial.print(day_gradient); Serial.println(")");
  grad_hr = day_gradient;
  grad_mn = day_gradient;
}

void animation_hour_gradient(){
  // handle animation(3)
  double hour_percent;
  int hour_gradient;
  hour_percent = (time_minute/60.0 + time_second/3600.0)*100;
  hour_gradient = map_double(hour_percent, 0, 100, 0, 240);
  //Serial.print("(hour_percent, hour_gradient): ("); Serial.print(hour_percent); Serial.print(", "); Serial.print(hour_gradient); Serial.println(")");
  grad_hr = hour_gradient;
  grad_mn = hour_gradient;
}

void animation_min_gradient(){
  // handle animation(4)
  double min_percent;
  int min_gradient;
  min_percent = (time_second/60.0)*100;
  min_gradient = map_double(min_percent, 0, 100, 0, 240);
  //Serial.print("(min_percent, min_gradient): ("); Serial.print(min_percent); Serial.print(", "); Serial.print(min_gradient); Serial.println(")");
  grad_hr = min_gradient;
  grad_mn = min_gradient;
}

void animation_const() {
  // handle animation(5)
  #ifdef TIME_ANIMATION_GRAD
    grad_hr = TIME_ANIMATION_GRAD;
    grad_mn = TIME_ANIMATION_GRAD;
  #else
    grad_hr =  50;
    grad_mn = 150;
  #endif
}

double map_double(double x2, double x1, double x3, double y1, double y3) {
  // same as the "map" but better because doubles!
  double y2;

  y2 = ( (x2 - x1) * (y3 - y1) ) / (x3 - x1);
  
  return y2;
}
