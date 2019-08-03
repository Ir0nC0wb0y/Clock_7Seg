void animation_cycle() {
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
}

void animation_day_gradient() {
  double day_percent;
  int day_gradient;
  day_percent = (time_hour_raw/24.0 + time_minute/1440.0 + time_second/86400.0)*100;
  day_gradient = map(day_percent, 0, 100, 0, 250);
  Serial.print("(day_percent, day_gradient): ("); Serial.print(day_percent); Serial.print(", "); Serial.print(day_gradient); Serial.println(")");
  grad_hr = day_gradient;
  grad_mn = day_gradient;
}

void animation_hour_gradient(){
  double hour_percent;
  int hour_gradient;
  hour_percent = (time_minute/60.0 + time_second/3600.0)*100;
  hour_gradient = map(hour_percent, 0, 100, 0, 250);
  Serial.print("(hour_percent, hour_gradient): ("); Serial.print(hour_percent); Serial.print(", "); Serial.print(hour_gradient); Serial.println(")");
  grad_hr = hour_gradient;
  grad_mn = hour_gradient;
}

void animation_min_gradient(){
  double min_percent;
  int min_gradient;
  min_percent = (time_second/60.0)*100;
  min_gradient = map(min_percent, 0, 100, 0, 250);
  Serial.print("(min_percent, min_gradient): ("); Serial.print(min_percent); Serial.print(", "); Serial.print(min_gradient); Serial.println(")");
  grad_hr = min_gradient;
  grad_mn = min_gradient;
}

void animation_const() {
  #ifdef TIME_ANIMATION_GRAD
    grad_hr = TIME_ANIMATION_GRAD;
    grad_mn = TIME_ANIMATION_GRAD;
  #else
    grad_hr =  50;
    grad_mn = 150;
  #endif
}
